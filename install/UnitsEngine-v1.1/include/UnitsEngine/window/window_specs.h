#pragma once
#include <string>

#include "UnitsEngine/window/window_flags.h"

namespace units {
  struct WindowSpecs final {
    std::string title= "new window";
    int width= 255, height= 255;
    WindowFlags flags= 0;
  };
} // namespace units