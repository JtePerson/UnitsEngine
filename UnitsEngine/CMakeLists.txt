set(UnitsEngine_SRC_DIR ${PROJECT_SOURCE_DIR}/UnitsEngine/src)
set(UnitsEngine_CPP_SRC
	${UnitsEngine_SRC_DIR}/test.cpp
)
add_library(UnitsEngine SHARED ${UnitsEngine_CPP_SRC})