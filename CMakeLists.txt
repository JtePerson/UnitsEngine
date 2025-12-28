cmake_minimum_required(VERSION 3.30)
project(UnitsEngine VERSION 1.0.0 DESCRIPTION "Game Engine for RisingWalls" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_SCAN_FOR_MODULES TRUE)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API TRUE)

configure_file(${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/config.hpp.in ${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/config.hpp)

include(${UnitsEngine_SOURCE_DIR}/cmake/config.cmake)

add_library(UnitsEngine SHARED)
add_library(Units::UnitsEngine ALIAS UnitsEngine)
target_compile_features(UnitsEngine
PUBLIC
  cxx_std_23
)

target_compile_definitions(UnitsEngine
PUBLIC
  $<$<CONFIG:Debug>:UE_ENABLE_LOGGING>
PRIVATE
  UE_BUILD_DLL
)

include(${UnitsEngine_SOURCE_DIR}/cmake/packages.cmake)
include(${UnitsEngine_SOURCE_DIR}/cmake/headers.cmake)

target_include_directories(UnitsEngine
PUBLIC
  $<BUILD_INTERFACE:${UnitsEngine_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
PRIVATE
)

include(${UnitsEngine_SOURCE_DIR}/cmake/modules.cmake)
include(${UnitsEngine_SOURCE_DIR}/cmake/cpp_files.cmake)

install(
  TARGETS UnitsEngine Modules
  EXPORT UnitsEngineExport
  FILE_SET cxx_modules DESTINATION modules/UnitsEngine
  FILE_SET header_files DESTINATION include
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static
)
install(
  EXPORT UnitsEngineExport
  FILE UnitsEngineConfig.cmake
  NAMESPACE Units::
  DESTINATION lib/cmake/UnitsEngine
)