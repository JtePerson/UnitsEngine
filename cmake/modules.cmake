include_guard()

set(UnitsEngineModules_SRC_FILES
  ${UnitsEngine_SOURCE_DIR}/modules/engine.mpp
  ${UnitsEngine_SOURCE_DIR}/modules/core/log.mpp
  ${UnitsEngine_SOURCE_DIR}/modules/layers.mpp
  ${UnitsEngine_SOURCE_DIR}/modules/memory/memory.mpp
  ${UnitsEngine_SOURCE_DIR}/modules/events/events.mpp
)

target_sources(UnitsEngine
PRIVATE
  FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS
      ${UnitsEngine_SOURCE_DIR}/modules
    FILES
      ${UnitsEngineModules_SRC_FILES}
)

add_library(Modules STATIC)
add_library(Units::Modules ALIAS Modules)
target_compile_features(Modules
PUBLIC
  cxx_std_23
)

target_compile_definitions(Modules
PUBLIC
  $<$<CONFIG:Debug>:UE_ENABLE_LOGGING>
)

target_include_directories(Modules
PUBLIC
  $<BUILD_INTERFACE:${UnitsEngine_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
PRIVATE
)

target_link_libraries(Modules
PRIVATE
  spdlog::spdlog_header_only
)

target_sources(Modules
PUBLIC
  FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS
      ${UnitsEngine_SOURCE_DIR}/modules
    FILES
      ${UnitsEngineModules_SRC_FILES}
)