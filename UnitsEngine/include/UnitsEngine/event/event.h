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

  #define UE_EVENT_TYPE(type) static inline ::units::EventType getType() noexcept { return static_cast<::units::EventType>(type); }
  #define UE_EVENT_CATEGORY(category) static inline uint64_t getCategory() noexcept { return category; }
} // namespace units