include_guard()

target_sources(UnitsEngine
PRIVATE
  ${UnitsEngine_SOURCE_DIR}/src/engine.cpp
  ${UnitsEngine_SOURCE_DIR}/src/core/log.cpp
  ${UnitsEngine_SOURCE_DIR}/src/layers.cpp
  ${UnitsEngine_SOURCE_DIR}/src/memory/memory.cpp
  ${UnitsEngine_SOURCE_DIR}/src/events/events.cpp
)