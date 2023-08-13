project(server)

add_executable(${PROJECT_NAME}
		server.c
		../common/common.c
#		accept_handler.c
#		recv_handler.c
	)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC ${LIBEVENT_INCLUDE_DIRS}
		PUBLIC ../common/
		)

target_link_libraries(${PROJECT_NAME} ${LIBEVENT_LIBRARIES})


