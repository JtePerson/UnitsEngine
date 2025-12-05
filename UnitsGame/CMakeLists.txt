set(UnitsGame_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsGame/src)
set(UnitsGame_CPP_DLL_SRC
  ${UnitsGame_SRC_DIR}/logic/game_layer.cpp
)
add_library(UnitsGameLogic SHARED ${UnitsGame_CPP_DLL_SRC})
target_include_directories(UnitsGameLogic
PUBLIC
  ${UnitsGame_SRC_DIR}/logic/include
PRIVATE
  ${UnitsGame_SRC_DIR}
)
target_link_libraries(UnitsGameLogic PRIVATE
  UnitsEngine::UnitsEngine
)
target_compile_definitions(UnitsGameLogic
PRIVATE
  GAME_BUILD_DLL
)

set(UnitsGame_CPP_EXE_SRC
	${UnitsGame_SRC_DIR}/game_application.cpp
	${UnitsGame_SRC_DIR}/entry.cpp
)
add_executable(UnitsGame ${UnitsGame_CPP_EXE_SRC})
target_include_directories(UnitsGame PRIVATE
  ${UnitsGame_SRC_DIR}
)
target_link_libraries(UnitsGame PRIVATE
  UnitsEngine::UnitsEngine
  UnitsGameLogic
)

if(WIN32)
  add_custom_command(TARGET UnitsGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:UnitsGame> $<TARGET_FILE_DIR:UnitsGame>
    COMMAND_EXPAND_LISTS
  )
endif()