#pragma once
#include "UnitsEngine/events/event_category.hpp"

#ifdef __INTELLISENSE__
#  include "../modules/events/events.mpp"
#endif

import units.Events;

namespace units {
  namespace Events {
    struct ApplicationQuitEvent final {
      // Header
      Type type= Type::ApplicationQuit;
      Category category= UE_EVENT_CATEGORY_APPLICATION;
      uint32_t size= sizeof(ApplicationQuitEvent);
      bool handled= false;
      // Data
    };
  } // namespace Events
} // namespace units