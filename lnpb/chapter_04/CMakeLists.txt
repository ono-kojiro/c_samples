project(chapter_04)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_04")

add_executable(client-timeout
	${CHAPTER_DIR}/client-timeout.c
)

