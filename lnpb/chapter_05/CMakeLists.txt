project(chapter_05)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_05")

add_executable(server2
	${CHAPTER_DIR}/server2.c
)

add_executable(server3
	${CHAPTER_DIR}/server3.c
)

add_executable(server4
	${CHAPTER_DIR}/server4.c
)

add_executable(server5
	${CHAPTER_DIR}/server5.c
)

add_executable(server6
	${CHAPTER_DIR}/server6.c
)

target_link_options(server6
  PUBLIC -lpthread
)

add_executable(server7
	${CHAPTER_DIR}/server7.c
)

add_executable(server8
	${CHAPTER_DIR}/server8.c
)

target_link_options(server8
  PUBLIC -lpthread
)

add_executable(server9
	${CHAPTER_DIR}/server9.c
)

target_link_options(server9
  PUBLIC -lpthread
)

add_executable(server9bug
	${CHAPTER_DIR}/server9bug.c
)

target_link_options(server9bug
  PUBLIC -lpthread
)

add_executable(telnet1
	${CHAPTER_DIR}/telnet1.c
)

add_executable(telnet2
	${CHAPTER_DIR}/telnet2.c
)

add_executable(telnet3
	${CHAPTER_DIR}/telnet3.c
)

add_executable(telnet4
	${CHAPTER_DIR}/telnet4.c
)

add_executable(telnet5
	${CHAPTER_DIR}/telnet5.c
)

target_link_options(telnet5
  PUBLIC -lpthread
)

add_executable(testclient
	${CHAPTER_DIR}/testclient.c
)

target_link_options(testclient
  PUBLIC -lpthread
)



