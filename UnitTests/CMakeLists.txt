set(UnitTests_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitTests/src)
set(UnitTests_CPP_SRC
	${UnitTests_SRC_DIR}/main.cpp
)
add_executable(UnitTests ${UnitTests_CPP_SRC})