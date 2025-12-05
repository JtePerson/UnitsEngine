#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "UnitsEngine::UnitsEngine" for configuration "Debug"
set_property(TARGET UnitsEngine::UnitsEngine APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(UnitsEngine::UnitsEngine PROPERTIES
  IMPORTED_IMPLIB_DEBUG "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libUnitsEngine.dll.a"
  IMPORTED_LOCATION_DEBUG "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/bin/libUnitsEngine.dll"
  )

list(APPEND _cmake_import_check_targets UnitsEngine::UnitsEngine )
list(APPEND _cmake_import_check_files_for_UnitsEngine::UnitsEngine "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libUnitsEngine.dll.a" "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/bin/libUnitsEngine.dll" )

# Import target "UnitsEngine::ImGui" for configuration "Debug"
set_property(TARGET UnitsEngine::ImGui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(UnitsEngine::ImGui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libImGui.a"
  )

list(APPEND _cmake_import_check_targets UnitsEngine::ImGui )
list(APPEND _cmake_import_check_files_for_UnitsEngine::ImGui "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libImGui.a" )

# Import target "UnitsEngine::SDL3-static" for configuration "Debug"
set_property(TARGET UnitsEngine::SDL3-static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(UnitsEngine::SDL3-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libSDL3.a"
  )

list(APPEND _cmake_import_check_targets UnitsEngine::SDL3-static )
list(APPEND _cmake_import_check_files_for_UnitsEngine::SDL3-static "C:/Users/Jesse/Desktop/Github/UnitsEngine/install/UnitsEngine-v1.1/lib/static/libSDL3.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
