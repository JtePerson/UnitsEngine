include(${PROJECT_SOURCE_DIR}/cmake/config.cmake)

if(${UnitsEngineInputs_BACKEND} STREQUAL "sdl3")
  set(SDL3_DIR ${UnitsEngine_DIR}/vendor/${UnitsEngine_COMPILER}/sdl3/cmake)
  find_package(SDL3 REQUIRED)
endif()