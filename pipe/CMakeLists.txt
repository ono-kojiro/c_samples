cmake_minimum_required(VERSION 3.13)

project(hello)

add_executable(hello
  main.c
)

target_link_libraries(hello m)

SET_TARGET_PROPERTIES(hello PROPERTIES OUTPUT_NAME "hello")

