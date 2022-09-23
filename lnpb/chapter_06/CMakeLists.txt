project(chapter_06)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_06")

add_executable(oneline
	${CHAPTER_DIR}/oneline.c
)

add_executable(bigclient
	${CHAPTER_DIR}/bigclient.c
)

add_executable(timeout
	${CHAPTER_DIR}/timeout.c
)

add_executable(bigserver
	${CHAPTER_DIR}/bigserver.c
)

add_executable(oneline1
	${CHAPTER_DIR}/oneline1.c
)

