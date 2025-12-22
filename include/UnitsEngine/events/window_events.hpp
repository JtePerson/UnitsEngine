#pragma once
#include "UnitsEngine/events/event_category.hpp"

#ifdef __INTELLISENSE__
#  include "../modules/events/events.mpp"
#endif

import units.events;

namespace units {
  namespace Events {
    struct WindowCloseEvent final {
      // Header
      Type type= Type::WindowClose;
      Category category= UE_EVENT_CATEGORY_WINDOW;
      uint32_t size= sizeof(WindowCloseEvent);
      bool handled= false;
      // Data
      uint64_t window_id= ~UINT64_C(0);
    };
  } // namespace Events
} // namespace units