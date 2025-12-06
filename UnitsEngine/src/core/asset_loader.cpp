#include "UnitsEngine/core/asset_loader.h"

#include <string>
#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"

namespace units {
  const char* AssetLoader::getBinPath() noexcept {
    static std::string base_filepath= []()->std::string {
      std::string filepath= SDL_GetBasePath();
      filepath.pop_back();
      return filepath;
    }();
    return base_filepath.c_str();
  }
} // namespace units