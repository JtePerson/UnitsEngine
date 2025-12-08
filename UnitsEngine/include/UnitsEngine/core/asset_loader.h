#pragma once
#include <string_view>

#include "UnitsEngine/core/engine_api.h"

namespace units {
class AssetLoader final {
 public:
  static constexpr std::string_view getRootPath() noexcept { return "../"; }
  static constexpr std::string_view getBinPath() noexcept { return "./"; }
  static constexpr std::string_view getAssetsPath() noexcept {
    return "../assets";
  }

 private:
};
}  // namespace units