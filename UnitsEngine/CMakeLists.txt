set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/src)
set(UnitsEngine_CPP_SRC
  ${UnitsEngine_SRC_DIR}/UnitsEngine/core/application.cpp
)

set(UnitsEngine_VENDOR_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/vendor)
add_subdirectory(${UnitsEngine_VENDOR_DIR}/spdlog)

add_library(UnitsEngine SHARED ${UnitsEngine_CPP_SRC})
target_include_directories(UnitsEngine PRIVATE
  ${UnitsEngine_SRC_DIR}
)