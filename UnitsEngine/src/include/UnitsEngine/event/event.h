#pragma once
#include "UnitsEngine/event/event_type.h"

#include <stdint.h>

namespace Units {
  class IEvent {
  public:
    friend class EventDispatcher;
  public:
    virtual inline ~IEvent() noexcept= default;
    virtual inline EventId getId() const noexcept= 0;
    virtual inline const char* getName() const noexcept= 0;
    inline bool handled() const noexcept { return m_handled_; }
  protected:
    inline IEvent() noexcept {}
    bool m_handled_= false;
  };
  #define UE_EVENT_TYPE(p_type) static  inline ::Units::EventId getStaticId() noexcept { return static_cast<::Units::EventId>(p_type); }\
                                virtual inline ::Units::EventId getId() const noexcept override { return static_cast<::Units::EventId>(p_type); }\
                                virtual inline const char* getName() const noexcept override { return #p_type; }
} // namespace Units

#include "UnitsEngine/event/event_listener.h"
#include "UnitsEngine/event/event_dispatcher.h"