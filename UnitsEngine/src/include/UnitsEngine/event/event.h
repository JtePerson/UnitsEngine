#pragma once
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/types/bool.h"
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/event/event_category.h"

namespace units {
  struct Event {
    EventType type= kUE_EventTypeNone;
    EventCategory category= UE_EVENTCATEGORY_NONE;
    size_t size= sizeof(Event);
    bool handled= true;
  };
} // namespace units