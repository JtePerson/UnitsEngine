include_guard()

include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
  GIT_TAG v1.16.0
  FIND_PACKAGE_ARGS NAMES spdlog
)

FetchContent_MakeAvailable(spdlog)
target_link_libraries(UnitsEngine
PUBLIC
  spdlog::spdlog
)