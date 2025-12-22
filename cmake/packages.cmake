include_guard()

include(${UnitsEngine_SOURCE_DIR}/cmake/config.cmake)

include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
  GIT_TAG v1.16.0
  FIND_PACKAGE_ARGS NAMES spdlog
)
Fetchcontent_Declare(
  glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw.git"
  GIT_TAG 3.4
  FIND_PACKAGE_ARGS NAMES glfw
)

FetchContent_MakeAvailable(spdlog)
target_link_libraries(UnitsEngine
PUBLIC
  spdlog::spdlog
)

if(${UnitsEngine_WINDOW_INPUT_BACKEND} STREQUAL "glfw")
  FetchContent_MakeAvailable(glfw)
  target_link_libraries(UnitsEngine
  PRIVATE
    glfw
  )
  target_compile_definitions(UnitsEngine
  PUBLIC
    UE_INCLUDE_GLFW
  )
endif()

if(${UnitsEngine_RENDER_BACKEND} STREQUAL "vulkan" AND DEFINED ENV{VULKAN_SDK})
  find_package(Vulkan REQUIRED)
  target_link_libraries(UnitsEngine
  PRIVATE
    Vulkan::Vulkan
  )
  target_compile_definitions(UnitsEngine
  PUBLIC
    UE_INCLUDE_VULKAN
  )
else()
  message(SEND_ERROR "Vulkan not found!")
endif()