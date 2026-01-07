include_guard()

include(${UnitsEngine_SOURCE_DIR}/cmake/config.cmake)

target_sources(UnitsEngine
PUBLIC
  FILE_SET header_files TYPE HEADERS
    BASE_DIRS
      ${UnitsEngine_SOURCE_DIR}/include
    FILES
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/config.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/core/engine_api.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/core/log.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/core/macros.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/core/platform_defines.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/events/application_events.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/events/event_category.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/events/window_events.hpp"
      "${UnitsEngine_SOURCE_DIR}/include/UnitsEngine/gpu/${UnitsEngine_RENDER_BACKEND}/gpu.hpp"
)