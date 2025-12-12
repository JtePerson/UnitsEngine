#pragma once
#include <concepts>
#include <functional>
#include <utility>
#include <vector>

#include <stdint.h>

#include "UnitsEngine/core/types.h"

namespace units {
  namespace Events {
    enum Type : uint32_t {
      Type_NONE= 0,
      Type_APPLICATION_QUIT,
    };
    using Category= uint64_t;

#define UE_EVENT_CATEGORY_NONE UINT64_C(0)
#define UE_EVENT_CATEGORY_APPLICATION (UINT64_C(1) << 0u )

    struct Event final {
      uint32_t type= Type_NONE;
      Category category= UE_EVENT_CATEGORY_NONE;
      uint32_t byte_count= sizeof(Event);
      bool handled= true;
    };

    template <typename T>
    concept CEvent= requires(T p_t) { { p_t.getType() }-> std::same_as<uint32_t>; } &&
                    requires(T p_t) { { p_t.getCategory() } -> std::same_as<Category>; } &&
                    ue_standard_layout<T> &&
                    ue_trivial<T>;

    class EventBus final {
     public:
      inline EventBus() noexcept= default;
      inline ~EventBus() noexcept= default;

      template <CEvent EventT>
      void pushEvent(const EventT* p_event_ptr) noexcept {
        pushEvent(reinterpret_cast<const void*>(p_event_ptr), EventT::getType(), EventT::getCategory(), sizeof(EventT));
      }

      inline void clear() noexcept {
        m_buffer_.clear();
        ++m_clear_epoch_;
      }

      class Iterator final {
       public:
        using iterator_category= std::forward_iterator_tag;
        using value_type= std::pair<const Event*, const void*>;
        using difference_type= std::ptrdiff_t;
        using pointer= value_type*;
        using reference= value_type;

       public:
        inline Iterator(const EventBus* p_owner_ptr, const ue_byte_t* p_byte_ptr) noexcept
            : m_owner_ptr_(p_owner_ptr), m_byte_ptr_(p_byte_ptr), m_generation_(p_owner_ptr->m_generation_), m_clear_epoch_(p_owner_ptr->m_clear_epoch_) {}

        inline Iterator(Iterator&&) noexcept= default;
        inline Iterator(const Iterator&) noexcept= default;
        inline Iterator& operator=(Iterator&&) noexcept= default;
        inline Iterator& operator=(const Iterator&) noexcept= default;

        inline bool operator==(const Iterator& p_other) const noexcept { return m_owner_ptr_ == p_other.m_owner_ptr_ && m_byte_ptr_ == p_other.m_byte_ptr_; }
        inline bool operator!=(const Iterator& p_other) const noexcept { return !(*this == p_other); }

        inline reference operator*() const noexcept {
          const Event* event_ptr= reinterpret_cast<const Event*>(m_byte_ptr_);
          const void* data_ptr= m_byte_ptr_ + sizeof(Event);
          return {event_ptr, data_ptr};
        }
        inline pointer operator->() const noexcept {
          // Return a temporary pointer to a static value (not ideal, but works for STL)
          static value_type tmp;
          tmp= (*this).operator*();
          return &tmp;
        }

        inline Iterator& operator++() noexcept {
          const Event* event_ptr= reinterpret_cast<const Event*>(m_byte_ptr_);
          m_byte_ptr_+= sizeof(Event) + event_ptr->byte_count;
          return *this;
        }
        inline Iterator operator++(int) noexcept {
          Iterator tmp= *this;
          ++(*this);
          return tmp;
        }

        inline bool valid() const noexcept { return m_generation_ == m_owner_ptr_->m_generation_ && m_clear_epoch_ == m_owner_ptr_->m_clear_epoch_; }

       private:
        const EventBus* m_owner_ptr_;
        const ue_byte_t* m_byte_ptr_;
        size_t m_generation_;
        size_t m_clear_epoch_;
      };

      inline Iterator begin() const noexcept { return Iterator(this, m_buffer_.data()); }
      inline Iterator end() const noexcept { return Iterator(this, m_buffer_.data() + m_buffer_.size()); }

      bool pollEvents(Event* p_event_ptr, const void*& p_data_ptr) noexcept;

     private:
      std::vector<ue_byte_t> m_buffer_;
      uint32_t m_generation_= 0u;
      uint32_t m_clear_epoch_= 0u;

      Iterator m_polling_it= end();

      void pushEvent(const void* p_event, const uint32_t& p_type, const Category& p_category, const uint32_t& p_byte_count) noexcept;
    };

    class EventDispatcher final {
     public:
      inline EventDispatcher() noexcept= default;
      inline ~EventDispatcher() noexcept= default;

      template <CEvent EventT, typename CallableT>
      inline void registerListener(CallableT&& p_listener) noexcept {
        const auto type_i= static_cast<size_t>(EventT::getType());
        if (type_i >= m_listeners_.size())
          m_listeners_.resize(type_i + 1);
        m_listeners_[type_i].emplace_back(makeWrapper<EventT>(p_listener));
      }

      void dispatch(Event* p_event_ptr, const void* p_data_ptr) noexcept;

     private:
      using ListenerFunc= std::function<void(Event*, const void*)>;

      template <typename CallableT>
      struct CallableTraits;

      template <typename ClassT, typename EventType>
      struct CallableTraits<bool (ClassT::*)(EventType&) const> {
        using EventT= EventType;
      };

      std::vector<std::vector<ListenerFunc>> m_listeners_{};

      template <CEvent EventT>
      inline ListenerFunc makeWrapper(const std::function<bool(EventT&)>& p_listener) noexcept {
        return [p_listener](Event* p_event, const void* p_data_ptr) -> void {
          auto* data_ptr= reinterpret_cast<EventT*>(const_cast<void*>(p_data_ptr));
          p_event->handled|= p_listener(*data_ptr);
        };
      }

      void dispatchTo(const std::vector<ListenerFunc>& p_listeners, Event* p_event, const void* p_data_ptr) noexcept;
    };
  } // namespace Events
} // namespace units

#define UE_EVENT_TYPE(type) static inline uint32_t getType() noexcept { return static_cast<uint32_t>(type); }
#define UE_EVENT_CATEGORY(category) static inline uint64_t getCategory() noexcept { return static_cast<uint64_t>(category); }