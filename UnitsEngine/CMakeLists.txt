cmake_minimum_required(VERSION 3.21)
project(UnitsEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(${PROJECT_SOURCE_DIR}/cmake/config.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/cpp_files.cmake)

set(UnitsEngine_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/InputEngines)

add_library(UnitsEngine SHARED ${UnitsEngine_CXX_FILES})
add_library(UnitsEngine::UnitsEngine ALIAS UnitsEngine)

target_compile_definitions(UnitsEngine
PUBLIC
PRIVATE
  $<$<CONFIG:Debug>:UE_BUILD_DEBUG>
  $<$<CONFIG:Release>:UE_BUILD_RELEASE>
  UE_BUILD_DLL
)

target_link_libraries(UnitsEngine
PUBLIC
PRIVATE
  UnitsEngine::Inputs
)

target_include_directories(UnitsEngine
PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

if(WIN32)
  add_custom_command(TARGET UnitsEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:UnitsEngine> $<TARGET_FILE_DIR:UnitsEngine>
    COMMAND_EXPAND_LISTS
  )
endif()