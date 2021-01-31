add_executable(check_hello src/check_hello.c)
include_directories(${CMAKE_SOURCE_DIR}/libhello/src)
target_link_libraries(check_hello hello)
target_link_libraries(check_hello ${LIBCHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(check_test2 src/check_test2.c)
#target_link_libraries(check_test2 check)

