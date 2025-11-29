#pragma once
#include <string>
#include <stdint.h>

#include "UnitsEngine/window/window_flags.h"

namespace Units {
  struct WindowSpecs final {
    std::string title= "";
    int width= 100, height= 100;
    WindowFlags flags= 0;
  };
} // namespace Units