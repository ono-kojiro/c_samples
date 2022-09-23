project(chapter_01)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_01")

add_executable(server
	${CHAPTER_DIR}/server.c
)

add_executable(client
	${CHAPTER_DIR}/client.c
)

