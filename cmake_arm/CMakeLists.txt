cmake_minimum_required(VERSION 3.13)

set(CMAKE_DISABLE_IN_SOURCE_BUilD ON)

set(CMAKE_SYSTEM_NAME Linux)

set(TARGET "arm-none-eabi")

project(arm_sample)
set(PROJECT_VERSION 0.0.1)

set(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions("-DTOP_MACRO=1")

find_package(PkgConfig REQUIRED)

# search libcheck
#pkg_check_modules(LIBCHECK check REQUIRED)

get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)

if ("${LIB64}" STREQUAL "TRUE")
	set(LIBSUFFIX 64)
else()
	set(LIBSUFFIX "")
endif()

set(INSTALL_LIB_DIR     lib${LIBSUFFIX} CACHE PATH "Installation directory for libraries")
mark_as_advanced(INSTALL_LIB_DIR)

add_subdirectory(libhoge ${CMAKE_CURRENT_BINARY_DIR}/libhoge)
add_subdirectory(libfoo  ${CMAKE_CURRENT_BINARY_DIR}/libfoo)
add_subdirectory(hello ${CMAKE_CURRENT_BINARY_DIR}/hello)
add_subdirectory(tests ${CMAKE_CURRENT_BINARY_DIR}/tests)

set(CMAKE_VERBOSE_MAKEFILE 1)

# testcase
enable_testing()

