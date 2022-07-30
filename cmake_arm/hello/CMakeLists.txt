project(main)

set(SRCS
  src/main.c
)

add_executable(main
  ${SRCS}
)

add_definitions(-DHELLO_MACRO=1 -DMAIN_MACRO=1)
remove_definitions(-DTOP_MACRO=1)

include_directories(${CMAKE_SOURCE_DIR}/libhoge/inc)
include_directories(${CMAKE_SOURCE_DIR}/libfoo/inc)

target_link_libraries(main hoge foo ${LIBCHECK_LIBRARIES})

target_link_options(main
  PUBLIC -specs=rdimon.specs)

SET_TARGET_PROPERTIES(main PROPERTIES OUTPUT_NAME "hello")

INSTALL(TARGETS main RUNTIME DESTINATION bin)


