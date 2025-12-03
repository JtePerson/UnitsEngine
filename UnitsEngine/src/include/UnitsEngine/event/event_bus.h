#pragma once
#include <vector>

#include "UnitsEngine/event/event.h"
#include "UnitsEngine/core/log.h"

namespace units {
  class EventBus final {
  public:
    friend class IApplication;
  public:
    template<typename EventT>
    inline void push(const EventT& p_event) noexcept {
      static_assert(std::is_standard_layout<EventT>::value, "EventT must be POD!");
      static_assert(std::is_trivially_copyable<EventT>::value, "EventT must be POD!");

      const size_t k_old_capacity= m_event_buffer_.capacity();
      const size_t k_old_size= m_event_buffer_.size();
      m_event_buffer_.resize(k_old_size + sizeof(Event) + sizeof(EventT));

      if (m_event_buffer_.capacity() != k_old_capacity) {
        ++m_generation_;
      }

      const Event header{.type= EventT::getType(), .category= EventT::getCategory(), .size= sizeof(EventT), .handled= false };
      std::memcpy(m_event_buffer_.data() + k_old_size, &header, sizeof(Event));
      std::memcpy(m_event_buffer_.data() + k_old_size + sizeof(Event), &p_event, sizeof(EventT));
    }
  private:
    class Iterator final {
    public:
      using iterator_category= std::forward_iterator_tag;
      using value_type= std::pair<const Event*, const void*>;
      using difference_type= std::ptrdiff_t;
      using pointer= value_type*;
      using reference= value_type;
    public:
      inline Iterator(const EventBus* p_owner_ptr, const std::byte* p_ptr) noexcept
      : m_owner_ptr_(p_owner_ptr), m_ptr_(p_ptr), m_generation_(p_owner_ptr->m_generation_), m_clear_epoch_(p_owner_ptr->m_clear_epoch_)
      {}

      inline Iterator(Iterator&&) noexcept= default;
      inline Iterator(const Iterator&) noexcept= default;
      inline Iterator& operator=(Iterator&&) noexcept= default;
      inline Iterator& operator=(const Iterator&) noexcept= default;

      inline bool operator==(const Iterator& p_other) const noexcept { return m_ptr_ == p_other.m_ptr_; }
      inline bool operator!=(const Iterator& p_other) const noexcept { return !(*this == p_other); }

      inline reference operator*() const noexcept {
        const Event* header_ptr= reinterpret_cast<const Event*>(m_ptr_);
        const void* data_ptr= m_ptr_ + sizeof(Event);
        return {header_ptr, data_ptr};
      }
      inline pointer operator->() const noexcept {
        // Return a temporary pointer to a static value (not ideal, but works for STL)
        static value_type tmp;
        tmp= (*this).operator*();
        return &tmp;
      }

      inline Iterator& operator++() noexcept {
        const Event* header_ptr= reinterpret_cast<const Event*>(m_ptr_);
        m_ptr_ += sizeof(Event) + header_ptr->size;
        return *this;
      }
      inline Iterator operator++(int) noexcept {
        Iterator tmp= *this;
        ++(*this);
        return tmp;
      }

      inline bool valid() const noexcept {
        return m_generation_ == m_owner_ptr_->m_generation_ && m_clear_epoch_ == m_owner_ptr_->m_clear_epoch_;
      }
    private:
      const EventBus* m_owner_ptr_;
      const std::byte* m_ptr_;
      size_t m_generation_;
      size_t m_clear_epoch_;
    };
  private:
    std::vector<std::byte> m_event_buffer_;
    size_t m_generation_= 0;
    size_t m_clear_epoch_= 0;
    
    Iterator m_polling_iterator= end();

    inline Iterator begin() const noexcept { return Iterator(this, m_event_buffer_.data()); }
    inline Iterator end() const noexcept { return Iterator(this, m_event_buffer_.data() + m_event_buffer_.size()); }

    inline void clear() noexcept {
      m_event_buffer_.clear();
      ++m_clear_epoch_;
    }

    inline bool pollEvents(Event& p_event, const void*& p_data_ptr) noexcept {
      if (!m_polling_iterator.valid()) {
        m_polling_iterator= begin();
      }
      if (m_polling_iterator == end()) {
        clear();
        return false;
      }
      auto [header_ptr, data_ptr]= *m_polling_iterator++;
      p_event= *header_ptr;
      p_data_ptr= data_ptr;
      return true;
    }
  };
} // namespace units