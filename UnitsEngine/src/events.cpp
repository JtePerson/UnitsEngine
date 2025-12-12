#include "UnitsEngine/events.h"

namespace units {
  namespace Events {
    void EventBus::pushEvent(const void* p_event, const uint32_t& p_type, const Category& p_category, const uint32_t& p_byte_count) noexcept {
      const uint32_t k_old_capacity= m_buffer_.capacity();
      const uint32_t k_old_byte_count= m_buffer_.size();
      m_buffer_.resize(k_old_byte_count + sizeof(Event) + p_byte_count);

      if (m_buffer_.capacity() != k_old_capacity)
        ++m_generation_;

      const Event event{
        .type= p_type,
        .category= p_category,
        .byte_count= p_byte_count,
        .handled= false,
      };
      std::memcpy(m_buffer_.data() + k_old_byte_count, &event, sizeof(Event));
      std::memcpy(m_buffer_.data() + k_old_byte_count + sizeof(Event), &p_event, p_byte_count);
    }

    bool EventBus::pollEvents(Event* p_event_ptr, const void*& p_data_ptr) noexcept {
      if (!m_polling_it.valid()) {
        m_polling_it= begin();
      }
      if (m_polling_it == end()) {
        clear();
        return false;
      }
      auto [header_ptr, data_ptr]= *m_polling_it++;
      *p_event_ptr= *header_ptr;
      p_data_ptr= data_ptr;
      return true;
    }

    void EventDispatcher::dispatch(Event* p_event_ptr, const void* p_data_ptr) noexcept {
      const auto type_i= static_cast<size_t>(p_event_ptr->type);
      if (type_i >= m_listeners_.size())
        m_listeners_.resize(type_i + 1);
      dispatchTo(m_listeners_[type_i], p_event_ptr, p_data_ptr);
    }

    void EventDispatcher::dispatchTo(const std::vector<ListenerFunc>& p_listeners, Event* p_event, const void* p_data_ptr) noexcept {
      for (auto& listener : p_listeners) {
        listener(p_event, p_data_ptr);
        if (p_event->handled) {
          break;
        }
      }
    }
  } // namespace Events
} // namespace units