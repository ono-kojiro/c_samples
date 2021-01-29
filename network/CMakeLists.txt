cmake_minimum_required(VERSION 2.8)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

project(build_lnpb C)

find_package(PkgConfig)
find_package(BISON REQUIRED)
find_package(FLEX  REQUIRED)

pkg_check_modules(OPENSSL REQUIRED openssl)
pkg_check_modules(LIBEVENT REQUIRED libevent)

add_subdirectory(server ${CMAKE_BINARY_DIR}/server)
add_subdirectory(client ${CMAKE_BINARY_DIR}/client)
add_subdirectory(receiver ${CMAKE_BINARY_DIR}/receiver)
add_subdirectory(sender ${CMAKE_BINARY_DIR}/sender)

set(CMAKE_VERBOSE_MAKEFILE 1)


