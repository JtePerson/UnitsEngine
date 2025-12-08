cmake_minimum_required(VERSION 3.10)
project(UnitsEngine VERSION 1.0 LANGUAGES CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor)

set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
include(${PROJECT_SOURCE_DIR}/cmake/engine_src_files.cmake)

add_library(UnitsEngine SHARED ${UnitsEngine_SRC_FILES})
add_library(UnitsEngine::UnitsEngine ALIAS UnitsEngine)

target_include_directories(UnitsEngine
PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(UnitsEngine
PUBLIC
  spdlog::spdlog
PRIVATE
  SDL3::SDL3-static
)

target_compile_definitions(UnitsEngine
PUBLIC
  UE_ENABLE_LOGGING
  UE_ENABLE_DEBUG
  UE_ENABLE_ASSERT
PRIVATE
  UE_BUILD_DLL
)