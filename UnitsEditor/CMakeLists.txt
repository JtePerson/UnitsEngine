set(UnitsEditor_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEditor/src)
set(UnitsEditor_CPP_SRC
	${UnitsEditor_SRC_DIR}/editor_layer.cpp
	${UnitsEditor_SRC_DIR}/editor_application.cpp
	${UnitsEditor_SRC_DIR}/entry.cpp
)
add_executable(UnitsEditor ${UnitsEditor_CPP_SRC})
target_include_directories(UnitsEditor PRIVATE
  ${UnitsEditor_SRC_DIR}
)
target_link_libraries(UnitsEditor PRIVATE
  UnitsEngine
  UnitsGameLogic
)
if(WIN32)
  add_custom_command(TARGET UnitsEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:UnitsEngine> $<TARGET_FILE_DIR:UnitsEditor>
  )
  add_custom_command(TARGET UnitsEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:UnitsGameLogic> $<TARGET_FILE_DIR:UnitsEditor>
  )
endif()