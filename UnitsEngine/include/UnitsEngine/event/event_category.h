#pragma once
#include "UnitsEngine/core/macros.h"
#include "UnitsEngine/types/number.h"

namespace units {
  constexpr Id k_UserEventCategoryStart= 5u;
  using EventCategory= uint64_t;
} // namespace units

#define UE_EVENTCATEGORY_NONE 0ull
#define UE_EVENTCATEGORY_USER (~0ull << units::k_UserEventCategoryStart)