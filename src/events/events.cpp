module;

#include <string>

#include <stdint.h>

module units.Events;

namespace units {
  namespace Events {
    bool EventBus::pushEvent(Event* p_event_ptr, const size_t& p_size) noexcept {
      if (m_buffer_usage_ + p_size > m_buffer_.size())
        return false;
      auto* event_ptr= reinterpret_cast<Event*>(m_buffer_(p_size, m_buffer_next_byte_));
      if (event_ptr == nullptr) {
        if (p_size > m_buffer_.index(m_buffer_start_byte_))
          return false;
        if (m_buffer_usage_ != 0u) {
          auto* newest_event_ptr= reinterpret_cast<Event*>(m_buffer_(sizeof(Event), m_newest_event_));
          newest_event_ptr->size= m_buffer_.size() - m_buffer_.index(m_buffer_start_byte_ + (m_buffer_usage_-= newest_event_ptr->size));
          m_buffer_usage_+= newest_event_ptr->size;
        } else {
          m_buffer_start_byte_= 0u;
        }
        m_buffer_next_byte_= 0u;
        event_ptr= reinterpret_cast<Event*>(m_buffer_(p_size, m_buffer_next_byte_));
      }
      std::memcpy(event_ptr, p_event_ptr, p_size);
      event_ptr->size= p_size;
      m_newest_event_= m_buffer_next_byte_;
      m_buffer_next_byte_+= p_size;
      m_buffer_usage_+= p_size;

      return true;
    }

    bool EventBus::pollEvent(Event*& p_event_ptr) noexcept {
      if (m_buffer_usage_ < sizeof(Event)) {
        m_buffer_start_byte_= 0u;
        m_buffer_next_byte_= m_buffer_start_byte_;
        m_buffer_usage_= 0u;
        m_newest_event_= UINT64_MAX;
        return false;
      }
      p_event_ptr= reinterpret_cast<Event*>(m_buffer_(sizeof(Event), m_buffer_start_byte_));
      if (p_event_ptr == nullptr)
        return false;
      m_buffer_start_byte_= m_buffer_.index(m_buffer_start_byte_ + p_event_ptr->size);
      m_buffer_usage_-= p_event_ptr->size;
      return true;
    }
  } // namespace Events
} // namespace units