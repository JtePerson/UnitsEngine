#pragma once
#include <string>
#include <filesystem>

#include "UnitsEngine/core/engine_api.h"

namespace units {
  struct UE_API AssetLoader final {
    static const char* getBinPath() noexcept;
    static inline const std::string& getAssetPath() noexcept {
      static std::string asset_filepath= [&]()->std::string {
        const std::filesystem::path bin_filepath(static_cast<std::string>(getBinPath()));
        if (std::filesystem::exists(bin_filepath) && std::filesystem::is_directory(bin_filepath)) {
          if (bin_filepath.filename() == "bin") {
            return static_cast<std::string>(getBinPath()) + "/../assets";
          }
        }
        return static_cast<std::string>(getBinPath()) + "/../../../assets";
      }();
      return asset_filepath;
    }
  };
} // namespace units
