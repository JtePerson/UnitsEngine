add_subdirectory(${UnitsEngine_VENDOR_DIR}/spdlog)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl)
add_subdirectory(${UnitsEngine_VENDOR_DIR}/sdl_image)

set(GLM_BUILD_TESTS OFF)

add_subdirectory(${UnitsEngine_VENDOR_DIR}/glm)

set(ImGui_CPP_SRC
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui_demo.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui_draw.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui_tables.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui_widgets.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui.cpp
)
set(ImGui_H_SRC_FILES
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imconfig.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui_internal.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imgui.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imstb_rectpack.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imstb_textedit.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/imstb_truetype.h
)
set(ImGui_BACKENDS_CPP_SRC
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdl3.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdlgpu3.cpp
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
set(ImGui_BACKENDS_H_SRC
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdl3.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdlgpu3.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdlgpu3_shaders.h
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui/backends/imgui_impl_sdlrenderer3.h
)
add_library(ImGui STATIC ${ImGui_CPP_SRC} ${ImGui_BACKENDS_CPP_SRC})
target_include_directories(ImGui
PUBLIC
  ${UnitsEngine_VENDOR_DIR}/imgui/include
PRIVATE
  ${UnitsEngine_VENDOR_DIR}/imgui/imgui
)
target_link_libraries(ImGui PRIVATE SDL3::SDL3-static)
file(MAKE_DIRECTORY ${UnitsEngine_VENDOR_DIR}/imgui/include/imgui)
foreach(ImGui_H_SRC ${ImGui_H_SRC_FILES})
  add_custom_command(TARGET ImGui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${ImGui_H_SRC} ${UnitsEngine_VENDOR_DIR}/imgui/include/imgui
  )
endforeach()
foreach(ImGui_BACKEND_H_SRC ${ImGui_BACKENDS_H_SRC})
  add_custom_command(TARGET ImGui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${ImGui_BACKEND_H_SRC} ${UnitsEngine_VENDOR_DIR}/imgui/include/imgui
  )
endforeach()