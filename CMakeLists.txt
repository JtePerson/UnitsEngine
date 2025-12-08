cmake_minimum_required(VERSION 3.10.0)
project(UnitsEngineRepo VERSION 1.0 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor)

add_subdirectory(${PROJECT_SOURCE_DIR}/UnitsEngine)
add_subdirectory(${PROJECT_SOURCE_DIR}/UnitsEditor)