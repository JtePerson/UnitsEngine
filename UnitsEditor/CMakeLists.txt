cmake_minimum_required(VERSION 3.10)
project(UnitsEditor VERSION 1.0 LANGUAGES CXX)

add_executable(UnitsEditor
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/UnitsEditor/project_loader.cpp
)

target_include_directories(UnitsEditor
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  $<BUILD_INTERFACE:${RapidJSON_SOURCE_DIR}/include>
)

target_link_libraries(UnitsEditor
PRIVATE
  UnitsEngine::UnitsEngine
  RapidJSON
)

if(WIN32)
  add_custom_command(TARGET UnitsEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:UnitsEditor> $<TARGET_FILE_DIR:UnitsEditor>
    COMMAND_EXPAND_LISTS
  )
endif()