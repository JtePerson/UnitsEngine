#pragma once
#include "UnitsEngine/event/event.h"
#include "UnitsEngine/event/event_listener.h"

#include <type_traits>

namespace Units {
  class EventDispatcher final {
  public:
    inline EventDispatcher(IEvent&& p_event_ptr) noexcept
    : m_event_ptr_{p_event_ptr}
    {}
    
    template<typename EventT>
    inline bool dispatch(const EventListener<EventT>& p_listener) const noexcept {
      static_assert((std::is_base_of<IEvent, EventT>::value && "EventType must derive from Event!"));
      if (EventT::getStaticId() == m_event_ptr_.getId()) {
        m_event_ptr_.m_handled_|= p_listener(static_cast<EventT&>(m_event_ptr_));
        return true;
      }
      return false;
    }
  private:
    IEvent& m_event_ptr_;
  };
} // namespace Units