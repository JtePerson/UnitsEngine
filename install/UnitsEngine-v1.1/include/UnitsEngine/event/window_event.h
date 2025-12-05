#pragma once
#include "UnitsEngine/event/event.h"
#include "UnitsEngine/window/window.h"

namespace units {
  struct WindowCloseEvent final {
    UE_EVENT_TYPE(kUE_EventTypeWindowClose)
    UE_EVENT_CATEGORY(UE_EVENTCATEGORY_NONE)
    Window* window_ptr;
  };
} // namespace units