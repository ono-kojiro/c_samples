add_executable(check_hoge src/check_hoge.c)
include_directories(${CMAKE_SOURCE_DIR}/libhoge/inc)
target_link_libraries(check_hoge hoge foo)
target_link_libraries(check_hoge ${LIBCHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(check_test2 src/check_test2.c)
#target_link_libraries(check_test2 check)

