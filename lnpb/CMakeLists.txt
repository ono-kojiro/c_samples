project(lnpb C)
cmake_minimum_required(VERSION 3.24)

find_package(FLEX 2.6.4)
find_package(BISON 3.8.2)

add_subdirectory(chapter_01)
add_subdirectory(chapter_03)
add_subdirectory(chapter_04)
add_subdirectory(chapter_05)
add_subdirectory(chapter_06)
add_subdirectory(chapter_08)
add_subdirectory(chapter_09)
add_subdirectory(chapter_10)
#add_subdirectory(chapter_11)
add_subdirectory(chapter_12)
enable_testing()

