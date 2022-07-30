project(hello)

set(SRCS
  src/main.c
)

add_executable(hello
  ${SRCS}
)

add_definitions(-DHELLO_MACRO=1 -DMAIN_MACRO=1)
remove_definitions(-DTOP_MACRO=1)

include_directories(${CMAKE_SOURCE_DIR}/libhoge/inc)
include_directories(${CMAKE_SOURCE_DIR}/libfoo/inc)

target_link_libraries(hello hoge foo ${LIBCHECK_LIBRARIES})

SET_TARGET_PROPERTIES(hello PROPERTIES OUTPUT_NAME "hello")

INSTALL(TARGETS hello RUNTIME DESTINATION bin)

include(${CMAKE_SOURCE_DIR}/cmake/options.cmake)
if(${USE_SPLINT})
  include(${CMAKE_SOURCE_DIR}/cmake/splint.cmake)
endif()

execute_splint(hello)


