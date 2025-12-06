set(UnitsEngine_VERSION "v1.1")
set(UnitsEngine_INSTALL_BIN_DIR    ${CMAKE_INSTALL_PREFIX}/bin)
set(UnitsEngine_INSTALL_LIB_DIR    ${CMAKE_INSTALL_PREFIX}/lib)
set(UnitsEngine_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)

set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/src)
set(UnitsEngine_CPP_SRC
  ${UnitsEngine_SRC_DIR}/core/log.cpp
  ${UnitsEngine_SRC_DIR}/core/asset_loader.cpp
  ${UnitsEngine_SRC_DIR}/iapplication.cpp
  ${UnitsEngine_SRC_DIR}/application.cpp
  ${UnitsEngine_SRC_DIR}/layer_factory.cpp
  ${UnitsEngine_SRC_DIR}/window/window.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_device.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_command_buffer.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_texture.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_render_pass.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_sampler.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_graphics_pipeline.cpp
  ${UnitsEngine_SRC_DIR}/gpu/gpu_shader.cpp
)

set(UnitsEngine_VENDOR_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/vendor)
add_subdirectory(${UnitsEngine_VENDOR_DIR})

add_library(UnitsEngine SHARED ${UnitsEngine_CPP_SRC})
add_library(UnitsEngine::UnitsEngine ALIAS UnitsEngine)

target_include_directories(UnitsEngine
PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/UnitsEngine/include>
  $<INSTALL_INTERFACE:${UnitsEngine_INSTALL_INCLUDE_DIR}>
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
  spdlog::spdlog_header_only
  ImGui
  glm::glm-header-only
PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/UnitsEngine/include/ DESTINATION ${UnitsEngine_INSTALL_INCLUDE_DIR})
install(DIRECTORY ${UnitsEngine_VENDOR_DIR}/spdlog/include/ DESTINATION ${UnitsEngine_INSTALL_INCLUDE_DIR})
install(DIRECTORY ${UnitsEngine_VENDOR_DIR}/imgui/include/ DESTINATION ${UnitsEngine_INSTALL_INCLUDE_DIR})
install(DIRECTORY ${UnitsEngine_VENDOR_DIR}/glm/glm/ DESTINATION ${UnitsEngine_INSTALL_INCLUDE_DIR}/glm FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl")

install(TARGETS UnitsEngine spdlog_header_only ImGui glm-header-only SDL3-static SDL3_Headers
	CONFIGURATIONS Debug
	EXPORT UnitsEngine_export
	RUNTIME  DESTINATION ${UnitsEngine_INSTALL_BIN_DIR}
	LIBRARY  DESTINATION ${UnitsEngine_INSTALL_LIB_DIR}
	ARCHIVE  DESTINATION ${UnitsEngine_INSTALL_LIB_DIR}/static
	INCLUDES DESTINATION ${UnitsEngine_INSTALL_INCLUDE_DIR}
)

set(UnitsEngine_PACKAGE_INSTALL_INCLUDE_DIR ${UnitsEngine_INSTALL_INCLUDE_DIR})
set(UnitsEngine_PACKAGE_INSTALL_LIB_DIR     ${UnitsEngine_INSTALL_LIB_DIR})
set(UnitsEngine_PACKAGE_NAME               "UnitsEngine")
set(UnitsEngine_PACKAGE_VERSION            ${UnitsEngine_VERSION})
set(UnitsEngine_PACKAGE_CMAKE_DIR ${UnitsEngine_INSTALL_LIB_DIR}/cmake/${UnitsEngine_PACKAGE_NAME})

configure_file(
  ${PROJECT_SOURCE_DIR}/UnitsEngine/cmake/UnitsEngine-config.cmake.in
  ${PROJECT_BINARY_DIR}/UnitsEngine/UnitsEngine-config.cmake
  @ONLY
)
configure_file(
  ${PROJECT_SOURCE_DIR}/UnitsEngine/cmake/UnitsEngine-config-version.cmake.in
  ${PROJECT_BINARY_DIR}/UnitsEngine/UnitsEngine-config-version.cmake
  @ONLY
)

install(EXPORT UnitsEngine_export
	NAMESPACE UnitsEngine::
	DESTINATION ${UnitsEngine_PACKAGE_CMAKE_DIR}
)
install(FILES
  ${PROJECT_BINARY_DIR}/UnitsEngine/UnitsEngine-config.cmake
  ${PROJECT_BINARY_DIR}/UnitsEngine/UnitsEngine-config-version.cmake
	DESTINATION ${UnitsEngine_PACKAGE_CMAKE_DIR}
)