#pragma once
#include <stdint.h>

namespace Units {
  using EventId= uint16_t;
  constexpr EventId k_UserEventStart= 100;
  enum class EventType : EventId {
    kNone= 0,
    kApplicationQuit,
    kWindowClose,
    kUser= k_UserEventStart
  };
} // namespace Units