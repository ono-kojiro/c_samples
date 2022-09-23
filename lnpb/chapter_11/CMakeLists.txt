project(chapter_11)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_11")

add_executable(ssl-server
	${CHAPTER_DIR}/ssl-server.c
)

target_compile_options(ssl-server
	PUBLIC -DUSE_DH -DCHECK_CLIENT_CERT
)

target_link_options(ssl-server
	PUBLIC -lssl -lcrypto
)

add_executable(ssl-client
	${CHAPTER_DIR}/ssl-client.c
)

target_compile_options(ssl-client
	PUBLIC -DCHECK_SERVER_CERT -DCHECK_CLIENT_CERT
)

target_link_options(ssl-client
	PUBLIC -lssl -lcrypto
)

