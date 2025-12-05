add_subdirectory(${UnitsEngine_VENDOR_DIR}/spdlog)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl)
add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl_image)

set(GLM_BUILD_TESTS OFF)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/glm)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/imgui)