project(libhoge)

set(SRCS
	src/hoge.c
)

add_library(hoge ${SRCS})

add_definitions(-DLIBHOGE_MACRO=1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/libfoo/inc)

INSTALL(TARGETS hoge ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
INSTALL(FILES inc/hoge.h DESTINATION include)

include(${CMAKE_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/splint.cmake)
execute_splint(hoge)

