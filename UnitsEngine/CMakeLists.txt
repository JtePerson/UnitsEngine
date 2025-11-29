set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/src)
set(UnitsEngine_CPP_SRC
  ${UnitsEngine_SRC_DIR}/core/log.cpp
  ${UnitsEngine_SRC_DIR}/core/application.cpp
  ${UnitsEngine_SRC_DIR}/core/layer.cpp
  ${UnitsEngine_SRC_DIR}/core/layer_stack.cpp
)

set(UnitsEngine_VENDOR_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/vendor)
add_subdirectory(${UnitsEngine_VENDOR_DIR}/spdlog)

add_library(UnitsEngine SHARED ${UnitsEngine_CPP_SRC})
target_include_directories(UnitsEngine
PUBLIC
  ${UnitsEngine_VENDOR_DIR}/spdlog/include
  ${UnitsEngine_SRC_DIR}/include
PRIVATE
  ${UnitsEngine_SRC_DIR}
)
target_compile_definitions(UnitsEngine
PRIVATE
  UE_BUILD_ENGINE
PUBLIC
  $<$<CONFIG:Debug>:UE_DEBUG>
  $<$<CONFIG:Debug>:UE_ASSERT_ENABLED>
  $<$<CONFIG:Debug>:UE_LOGGING_ENABLED>
)
target_compile_options(UnitsEngine
PRIVATE
  $<$<CONFIG:Debug>:-g -O0>
  $<$<CONFIG:Release>:-O3>
)