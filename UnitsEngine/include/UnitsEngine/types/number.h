#pragma once
#include <stdint.h>

namespace units {
  // Identifier
  using Id= uint32_t;
  constexpr Id k_null_Id= ~0u;
  // Index
  using I= uint32_t;
  constexpr Id k_null_I= ~0u;
  // Number/Count
  using N= uint32_t;
} // namespace units