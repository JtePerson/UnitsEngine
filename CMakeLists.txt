cmake_minimum_required(VERSION 3.28)
project(UnitsEngine VERSION 1.0.0 DESCRIPTION "Game Engine for RisingWalls" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_library(UnitsEngine SHARED)
add_library(Units::Engine ALIAS UnitsEngine)
target_compile_features(UnitsEngine
PRIVATE
  cxx_std_20
)

target_compile_definitions(UnitsEngine
PUBLIC
  UE_ENABLE_LOGGING
PRIVATE
  UE_BUILD_DLL
)

include(${UnitsEngine_SOURCE_DIR}/cmake/packages.cmake)

target_include_directories(UnitsEngine
PUBLIC
  $<BUILD_INTERFACE:${UnitsEngine_SOURCE_DIR}/include>
PRIVATE
)

include(${UnitsEngine_SOURCE_DIR}/cmake/modules.cmake)
include(${UnitsEngine_SOURCE_DIR}/cmake/cpp_files.cmake)