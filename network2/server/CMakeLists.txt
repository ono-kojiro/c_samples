project(server LANGUAGES C)

add_executable(${PROJECT_NAME}
		server.c
	)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC ${LIBEVENT_INCLUDE_DIRS}
		PUBLIC ../common/
		)

target_link_libraries(${PROJECT_NAME} ${LIBEVENT_LIBRARIES})

install(TARGETS ${PROJECT_NAME})

