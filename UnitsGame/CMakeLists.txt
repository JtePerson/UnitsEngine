set(UnitsGame_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsGame/src)
set(UnitsGame_CPP_DLL_SRC
  ${UnitsGame_SRC_DIR}/game.cpp
)
add_library(UnitsGameLogic SHARED ${UnitsGame_CPP_DLL_SRC})
target_include_directories(UnitsGameLogic PRIVATE
  ${UnitsGame_SRC_DIR}
)
target_link_libraries(UnitsGameLogic PRIVATE
  UnitsEngine
)

set(UnitsGame_CPP_EXE_SRC
	${UnitsGame_SRC_DIR}/main.cpp
)
add_executable(UnitsGame ${UnitsGame_CPP_EXE_SRC})
target_include_directories(UnitsGame PRIVATE
  ${UnitsGame_SRC_DIR}
)
target_link_libraries(UnitsGame PRIVATE
  UnitsEngine
)

if(WIN32)
  add_custom_command(TARGET UnitsGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:UnitsEngine> $<TARGET_FILE_DIR:UnitsGame>
  )
endif()