project(chapter_09)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_09")

add_executable(u-client-b2
	${CHAPTER_DIR}/u-client-b2.c
)

add_executable(u-server-m6
	${CHAPTER_DIR}/u-server-m6.c
)

add_executable(u-client-m
	${CHAPTER_DIR}/u-client-m.c
)

add_executable(u-client
	${CHAPTER_DIR}/u-client.c
)

add_executable(u-server-m
	${CHAPTER_DIR}/u-server-m.c
)

add_executable(u-client2
	${CHAPTER_DIR}/u-client2.c
)

add_executable(u-client-m6
	${CHAPTER_DIR}/u-client-m6.c
)

add_executable(u-server
	${CHAPTER_DIR}/u-server.c
)

add_executable(u-client-b
	${CHAPTER_DIR}/u-client-b.c
)

