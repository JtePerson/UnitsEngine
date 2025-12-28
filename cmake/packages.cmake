include_guard()

include(${UnitsEngine_SOURCE_DIR}/cmake/config.cmake)

include(FetchContent)

set(SPDLOG_INSTALL TRUE CACHE BOOL "" FORCE)
set(SPDLOG_HEADER_ONLY TRUE CACHE BOOL "" FORCE)
set(SPDLOG_USE_STD_FORMAT TRUE CACHE BOOL "" FORCE)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
  GIT_TAG v1.16.0
  FIND_PACKAGE_ARGS NAMES spdlog
)

FetchContent_MakeAvailable(spdlog)

target_link_libraries(UnitsEngine
PUBLIC
  spdlog::spdlog_header_only
)