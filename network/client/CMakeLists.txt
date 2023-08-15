project(client LANGUAGES C)

add_executable(${PROJECT_NAME}
		client.c
#		../common/common.c
#		recv_handler.c
	)

target_include_directories(${PROJECT_NAME}
		PUBLIC ${LIBEVENT_INCLUDE_DIRS}
		PUBLIC ../common/
		)

target_link_libraries(${PROJECT_NAME} ${LIBEVENT_LIBRARIES})

install(TARGETS client)

