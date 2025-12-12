#pragma once
#include "UnitsEngine/events.h"

namespace units {
  namespace Events {
    struct ApplicationQuitEvent final {
      UE_EVENT_TYPE(Type_APPLICATION_QUIT)
      UE_EVENT_CATEGORY(UE_EVENT_CATEGORY_APPLICATION)
    };
  } // namespace Events
} // namespace units