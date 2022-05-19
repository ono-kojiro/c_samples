#
# custom target for splint
#

function(execute_splint target)
	set(project ${PROJECT_NAME})
	get_target_property(srcs ${target} SOURCES)

	add_custom_target(splint-${project}
		COMMENT execute splint for ${srcs}
	)

	foreach(src ${srcs})
		add_custom_command(TARGET splint-${project}
			COMMAND mkdir -p `dirname ${src}`
			COMMAND splint -f ${CMAKE_CURRENT_BINARY_DIR}/options.txt 
				${CMAKE_CURRENT_SOURCE_DIR}/${src}
				> ${CMAKE_CURRENT_BINARY_DIR}/${src}.splint || true)
	endforeach()
endfunction()

