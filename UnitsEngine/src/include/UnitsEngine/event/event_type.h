#pragma once
#include "UnitsEngine/types/number.h"

namespace units {
  constexpr Id k_UserEventTypeStart= 100;
} // namespace units

enum EventType : units::Id {
  kUE_EventTypeNone= 0,
  kUE_EventTypeApplicationQuit,
  kUE_EventTypeEnd,
  kUE_EventTypeUser= units::k_UserEventTypeStart
};