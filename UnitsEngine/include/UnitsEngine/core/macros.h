#pragma once
#include <utility>

#define UE_EXPAND_MACRO(x) x
#define UE_STRINGIFY_MACRO(x) #x

#define UE_NODISCARD [[nodiscard]]

#define UE_BIND_FUNCTION(function)                                    \
  [this](auto&&... p_args) -> decltype(auto) {                        \
    return this->function(std::forward<decltype(p_args)>(p_args)...); \
  }

#define UE_SINGLE_BIT(i) (1 << i)