add_executable(test_hoge src/test_hoge.c)
include_directories(${CMAKE_SOURCE_DIR}/libhoge/inc)
target_link_libraries(test_hoge hoge foo)
target_link_libraries(test_hoge ${LIBCHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

target_link_options(test_hoge
  PUBLIC -specs=rdimon.specs
)

enable_testing()
add_test(NAME test_hoge COMMAND arm-none-eabi-run test_hoge)


