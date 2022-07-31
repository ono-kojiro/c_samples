cmake_minimum_required(VERSION 3.13)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   message(STATUS "CMAKE_SOURCE_DIR is ${CMAKE_SOURCE_DIR}")
   message(STATUS "CMAKE_BINARY_DIR is ${CMAKE_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

project(xv6-net)
set(PROJECT_VERSION 0.0.1)

set(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(OBJCOPY objcopy)
set(OBJDUMP objdump)

set(XV6_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(tools     ${CMAKE_BINARY_DIR}/tools)
add_subdirectory(bootblock ${CMAKE_BINARY_DIR}/bootblock)
add_subdirectory(bootblockother ${CMAKE_BINARY_DIR}/bootblockother)
add_subdirectory(initcode  ${CMAKE_BINARY_DIR}/initcode)
add_subdirectory(kernel    ${CMAKE_BINARY_DIR}/kernel)
add_subdirectory(user      ${CMAKE_BINARY_DIR}/user)
add_subdirectory(tests     ${CMAKE_BINARY_DIR}/tests)

