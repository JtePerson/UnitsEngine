include_guard()

include(${UnitsEngine_SOURCE_DIR}/cmake/config.cmake)

target_sources(UnitsEngine
PRIVATE
  ${UnitsEngine_SOURCE_DIR}/src/engine.cpp
  ${UnitsEngine_SOURCE_DIR}/src/core/log.cpp
  ${UnitsEngine_SOURCE_DIR}/src/layers.cpp
  ${UnitsEngine_SOURCE_DIR}/src/memory/memory.cpp
  ${UnitsEngine_SOURCE_DIR}/src/events/events.cpp
  ${UnitsEngine_SOURCE_DIR}/src/window/${UnitsEngine_WINDOW_INPUT_BACKEND}/window.cpp
  ${UnitsEngine_SOURCE_DIR}/src/inputs/${UnitsEngine_WINDOW_INPUT_BACKEND}/inputs.cpp
  ${UnitsEngine_SOURCE_DIR}/src/gpu/${UnitsEngine_RENDER_BACKEND}/gpu.cpp
)