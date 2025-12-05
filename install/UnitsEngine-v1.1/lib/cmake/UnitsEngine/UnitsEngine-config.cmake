# Minimal relocatable package config for UnitsEngine
# Located under: <prefix>/C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/cmake/UnitsEngine

# Compute install prefix from this file's location:
# .../lib/cmake/UnitsEngine/UnitsEngine-config.cmake  -> prefix is 3 levels up
get_filename_component(UnitsEngine ${CMAKE_CURRENT_LIST_DIR}/../../.. REALPATH)

include(CMakeFindDependencyMacro)
find_dependency(Threads REQUIRED)  # provides Threads::Threads

# Convenience variables for consumers
set(UnitsEngine_PREFIX        ${UnitsEngine})
set(UnitsEngine_INCLUDE_DIR   ${UnitsEngine}/C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/include)
set(UnitsEngine_LIBRARY_DIR   ${UnitsEngine}/C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib)

# Load exported targets (created by install(EXPORT ...))
include(${CMAKE_CURRENT_LIST_DIR}/UnitsEngine_export.cmake)

# Optionally expose a variable indicating availability
set(UnitsEngine_FOUND TRUE)
