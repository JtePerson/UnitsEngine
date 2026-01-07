#pragma once
#include <utility>

#define UE_EXPAND(x) x
#define UE_STRINGIFY(x) #x
#define UE_STRINGIFY_VALUE(x) UE_STRINGIFY(x)

#define UE_NODISCARD [[nodiscard]]

#define UE_BIND_FUNCTION(func) [this](auto&&... p_args)->decltype(auto){ return this->func(std::forward<decltype(p_args)>(p_args)...); }

#define UE_SINGLE_BIT(i) (1 << i)

#define UE_MIN(a, b) ((a) < (b) ? (a) : (b))
#define UE_MAX(a, b) ((a) > (b) ? (a) : (b))
#define UE_CLAMP(v, lo, hi) (UE_MIN(UE_MAX(v, lo), hi))