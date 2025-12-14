cmake_minimum_required(VERSION 3.21)
project(UnitsManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(${PROJECT_SOURCE_DIR}/cmake/units_manager_cpp_files.cmake)

add_executable(UnitsManager ${UnitsManager_CXX_FILES})

target_include_directories(UnitsManager
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(UnitsManager
PRIVATE
  # UnitsEngine::UnitsEngine
)

target_include_directories(UnitsManager
PRIVATE
  ${PROJECT_SOURCE_DIR}/../UnitsEngine/include
)

if(false)
  add_custom_command(TARGET UnitsManager POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:UnitsManager> $<TARGET_FILE_DIR:UnitsManager>
    COMMAND_EXPAND_LISTS
  )
endif()