cmake_minimum_required(VERSION 2.8)
#cmake_minimum_required(VERSION 3.13)

cmake_policy(SET CMP0048 NEW)
#cmake_policy(SET CMP0076 OLD)

#
# enable recursive target for custom target
# 
#cmake_policy(SET CMP0002 OLD)
#set_property(GLOBAL PROPERTY ALLOW_DUPLICTE_CUSTOM_TARGET ON)


#set(CMAKE_DISABLE_IN_SOURCE_BUilD ON)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

#project(cmake_sample C)
#project(cmake_sample NONE)
project(cmake_sample)
set(PROJECT_VERSION 1.0.4)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "$(CC)" FORCE)

add_definitions("-DTOP_MACRO=1")

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
# search libcheck
pkg_check_modules(LIBCHECK check REQUIRED)
#find_package(CHECK REQUIRED)
#include_directoreis(${CHECK_INCLUDE_DIRS})

# Check headers
set(INCLUDES "")
macro(ck_check_include_file header var)
  check_include_files("${INCLUDES};${header}" ${var})
  if(${var})
    set(INCLUDES ${INCLUDES} ${header})
  endif(${var})
endmacro(ck_check_include_file)

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
add_subdirectory(libhello ${CMAKE_CURRENT_BINARY_DIR}/libhello)
add_subdirectory(hello ${CMAKE_CURRENT_BINARY_DIR}/hello)
add_subdirectory(tests ${CMAKE_CURRENT_BINARY_DIR}/tests)

set(CMAKE_VERBOSE_MAKEFILE 1)

# add splint targets
add_custom_target(splint
	COMMAND cd libhoge  && make splint-libhoge
	COMMAND cd libfoo   && make splint-libfoo
	COMMAND cd libhello && make splint-libhello
	COMMAND cd hello    && make splint-hello
)

# testcase
enable_testing()
#add_test(test_hello test/test_hello)
add_test(NAME check_hello COMMAND check_hello)
#add_test(NAME check_test2 COMMAND check_test2)

# 'make package' creates tar.bz2 binary package
#set(CPACK_GENERATOR "TBZ2")
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}-bin")

# 'make package_source' create source package
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_OUTPUT_FILE_PREFIX "..")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "/_cmake_make/;/_abuild/;/autom4te.cache/;/.git/;/.svn/;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#	message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

