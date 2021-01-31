project(libfoo)

set(SRCS
	src/foo.c
)

add_library(foo ${SRCS})

add_definitions(-DLIBFOO_MACRO=1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

INSTALL(TARGETS foo ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(FILES inc/foo.h DESTINATION include)

include(${CMAKE_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/splint.cmake)

message(STATUS "libfoo's project name is ${PROJECT_NAME}")
message(STATUS "libfoo's target name is ${TARGET}")

execute_splint(foo)

