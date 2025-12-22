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

add_library(UnitsEngineModules STATIC)
add_library(Units::Modules ALIAS UnitsEngineModules)
target_compile_features(UnitsEngineModules
PUBLIC
  cxx_std_20
)

target_link_libraries(UnitsEngineModules
PUBLIC
  spdlog::spdlog
)

target_include_directories(UnitsEngineModules
PUBLIC
  $<BUILD_INTERFACE:${UnitsEngine_SOURCE_DIR}/include>
)

target_sources(UnitsEngineModules
PUBLIC
  FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS
      ${UnitsEngine_SOURCE_DIR}/modules
    FILES
      ${UnitsEngineModules_SRC_FILES}
)