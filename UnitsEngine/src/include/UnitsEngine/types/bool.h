#pragma once

using UE_bool_t= unsigned char;
constexpr UE_bool_t operator""_uc(unsigned long long p_v) noexcept {
  return static_cast<UE_bool_t>(p_v);
}
constexpr UE_bool_t kUE_TRUE= ~0_uc;
constexpr UE_bool_t kUE_FALSE= 0_uc;