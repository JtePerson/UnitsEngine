#pragma once
#include <array>
#include <vector>
#include <functional>

#include "UnitsEngine/event/event.h"
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/core/log.h"

namespace units {
  class EventDispatcher final {
  public:
    inline EventDispatcher(const size_t& p_user_event_count) noexcept
    : m_user_listeners_(p_user_event_count)
    {}

    template<typename EventT>
    inline void registerListener(Id p_type, const std::function<bool(EventT&)>& p_listener) noexcept {
      if (p_type < m_listeners_.size()) {
        m_listeners_[static_cast<size_t>(p_type)].emplace_back(makeWrapper<EventT>(p_listener));
      } else {
        p_type -= m_listeners_.size();
        if (p_type >= m_user_listeners_.size()) {
          m_user_listeners_.resize(p_type + 1);
        }
        m_user_listeners_[static_cast<size_t>(p_type)].emplace_back(makeWrapper<EventT>(p_listener));
      }
    }

    inline void dispatch(Event& p_event, const void* p_data_ptr) noexcept {
      auto type_i= static_cast<size_t>(p_event.type);
      if (type_i < m_listeners_.size()) {
        dispatchTo(m_listeners_[type_i], p_event, p_data_ptr);
      } else {
        type_i-= m_listeners_.size();
        if (type_i < m_user_listeners_.size()) {
          dispatchTo(m_user_listeners_[type_i], p_event, p_data_ptr);
        }
      }
    }
  private:
    using ListenerFunc= std::function<void(Event&, const void*)>;
  private:
    std::array<std::vector<ListenerFunc>, EventType::kUE_EventTypeEnd> m_listeners_;
    std::vector<std::vector<ListenerFunc>> m_user_listeners_;

    template<typename EventT>
    inline ListenerFunc makeWrapper(const std::function<bool(EventT&)>& p_listener) noexcept {
      return [p_listener](Event& p_event, const void* p_data_ptr){
        auto* data_ptr= reinterpret_cast<EventT*>(const_cast<void*>(p_data_ptr));
        p_event.handled|= p_listener(*data_ptr);
      };
    }

    inline void dispatchTo(const std::vector<ListenerFunc>& p_listeners, Event& p_event, const void* p_data_ptr) noexcept {
      for (auto listener : p_listeners) {
        listener(p_event, p_data_ptr);
        if (p_event.handled) {
          break;
        }
      }
    }
  };
} // namespace units