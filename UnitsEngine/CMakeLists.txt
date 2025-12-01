set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/src)
set(UnitsEngine_CPP_SRC
  ${UnitsEngine_SRC_DIR}/core/log.cpp
  ${UnitsEngine_SRC_DIR}/iapplication.cpp
  ${UnitsEngine_SRC_DIR}/application.cpp
  ${UnitsEngine_SRC_DIR}/layer_factory.cpp
)

set(UnitsEngine_VENDOR_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/vendor)
add_subdirectory(${UnitsEngine_VENDOR_DIR})

add_library(UnitsEngine SHARED ${UnitsEngine_CPP_SRC})
target_include_directories(UnitsEngine
PUBLIC
  ${UnitsEngine_SRC_DIR}/include
  ${UnitsEngine_VENDOR_DIR}/imgui
PRIVATE
  ${UnitsEngine_SRC_DIR}
)
target_compile_definitions(UnitsEngine
PUBLIC
  $<$<CONFIG:Debug>:UE_DEBUG>
  $<$<CONFIG:Debug>:UE_ASSERT_ENABLED>
  $<$<CONFIG:Debug>:UE_LOGGING_ENABLED>
PRIVATE
  UE_BUILD_ENGINE
)
target_compile_options(UnitsEngine
PRIVATE
  $<$<CONFIG:Debug>:-g -O0>
  $<$<CONFIG:Release>:-O3>
)
target_link_libraries(UnitsEngine
PUBLIC
  spdlog
  ImGui
  glm::glm-header-only
PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
)