#pragma once
#include "UnitsEngine/event/event.h"

namespace units {
  struct ApplicationQuitEvent final {
    UE_EVENT_TYPE(kUE_EventTypeApplicationQuit)
    UE_EVENT_CATEGORY(UE_EVENTCATEGORY_NONE)
  };
} // namespace units