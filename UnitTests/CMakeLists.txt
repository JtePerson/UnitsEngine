set(UnitTests_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitTests/src)
set(UnitTests_CPP_SRC
	${UnitTests_SRC_DIR}/test_layer.cpp
	${UnitTests_SRC_DIR}/test_application.cpp
	${UnitTests_SRC_DIR}/entry.cpp
)
add_executable(UnitTests ${UnitTests_CPP_SRC})
target_include_directories(UnitTests PRIVATE
  ${UnitTests_SRC_DIR}
)
target_link_libraries(UnitTests PRIVATE
  UnitsEngine
)
if(WIN32)
  add_custom_command(TARGET UnitTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:UnitsEngine> $<TARGET_FILE_DIR:UnitTests>
  )
endif()