add_subdirectory(${UnitsEngine_VENDOR_DIR}/spdlog)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl)
add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl_image)

file(GLOB_RECURSE ImGui_CPP_SRC ${UnitsEngine_VENDOR_DIR}/imgui/*.cpp)
add_library(ImGui STATIC ${ImGui_CPP_SRC})
target_include_directories(ImGui PUBLIC ${UnitsEngine_VENDOR_DIR}/imgui)
target_link_libraries(ImGui PRIVATE SDL3::SDL3-static)