project(chapter_03)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_03")

add_executable(daemon
	${CHAPTER_DIR}/daemon.c
)

target_compile_options(daemon
  PUBLIC -DUNIT_TEST
)

add_executable(server1
	${CHAPTER_DIR}/server1.c
)

add_executable(re-exec
	${CHAPTER_DIR}/re-exec.c
)

add_executable(signaltest
	${CHAPTER_DIR}/signaltest.c
)

target_compile_options(signaltest
  PUBLIC -DUSE_SIGNAL
)

add_executable(signaltest1
	${CHAPTER_DIR}/signaltest1.c
)


