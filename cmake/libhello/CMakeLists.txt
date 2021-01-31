project(libhello)

set(SRCS
	src/hello.c
	src/test.c
)
add_library(hello ${SRCS})

#add_library(hello "")
#target_sources(hello
#	PRIVATE
#	${CMAKE_CURRENT_SOURCE_DIR}/src/hello.c
#	${CMAKE_CURRENT_SOURCE_DIR}/src/test.c
#)

add_definitions(-DLIBHELLO_MACRO=1)

#SET_TARGET_PROPERTIES(hellolib PROPERTIES OUTPUT_NAME "hello")
#SET_TARGET_PROPERTIES(hellolib PROPERTIES PREFIX "lib")

INSTALL(TARGETS hello ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
INSTALL(FILES src/hello.h DESTINATION include)

include(${CMAKE_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/splint.cmake)
execute_splint(hello)

