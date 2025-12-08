cmake_minimum_required(VERSION 3.10)
project(UnitsEngineVendor)

set(RAPIDJSON_BUILD_DOC False)
set(RAPIDJSON_BUILD_EXAMPLES False)
set(RAPIDJSON_BUILD_CXX20 True)
add_subdirectory(${PROJECT_SOURCE_DIR}/rapidjson)