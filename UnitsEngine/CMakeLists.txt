cmake_minimum_required(VERSION 3.10)
project(UnitsEngine VERSION 1.0 LANGUAGES CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor)

add_executable(HelloWorld
  ${PROJECT_SOURCE_DIR}/src/helloworld.cpp
)

target_include_directories(HelloWorld
PUBLIC
  ${PROJECT_SOURCE_DIR}/include
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(HelloWorld
PRIVATE
  SDL3::SDL3-static
)