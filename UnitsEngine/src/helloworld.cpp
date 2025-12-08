#include <filesystem>
#include <iostream>

#include "UnitsEngine/core/asset_loader.h"

int main(int argc, char** argv) {
  std::filesystem::path root_path =
      std::filesystem::absolute(units::AssetLoader::getRootPath());
  std::filesystem::path bin_path =
      std::filesystem::absolute(units::AssetLoader::getBinPath());
  std::filesystem::path assets_path =
      std::filesystem::absolute(units::AssetLoader::getAssetsPath());
  std::cout << "Hello World!" << std::endl;
  std::cout << "Root path: " << root_path.string().c_str() << std::endl;
  std::cout << "Bin path: " << bin_path.string().c_str() << std::endl;
  std::cout << "Assets path: " << assets_path.string().c_str() << std::endl;
  return 0;
}