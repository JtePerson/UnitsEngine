cmake_minimum_required(VERSION 3.21)
project(UnitsEngineInputs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(${PROJECT_SOURCE_DIR}/cmake/config.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/cpp_files.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/find_backend.cmake)

add_library(UnitsEngineInputs STATIC ${UnitsEngineInputs_CPP_FILES})
add_library(UnitsEngine::Inputs ALIAS UnitsEngineInputs)

target_link_libraries(UnitsEngineInputs
PUBLIC
  $<$<STREQUAL:${UnitsEngineInputs_BACKEND},sdl3>:SDL3::SDL3-shared>
)

target_compile_definitions(UnitsEngineInputs
PRIVATE
  UE_BUILD_DLL
)

target_include_directories(UnitsEngineInputs
PRIVATE
  ${UnitsEngine_DIR}/include
)