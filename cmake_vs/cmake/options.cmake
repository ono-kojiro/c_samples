
set(OPTIONS_FILE ${CMAKE_CURRENT_BINARY_DIR}/options.txt)
file(REMOVE ${OPTIONS_FILE})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
	file(APPEND ${OPTIONS_FILE} "-I${dir}\n")
endforeach()

get_property(defs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	PROPERTY COMPILE_DEFINITIONS)
foreach(def ${defs})
		file(APPEND ${OPTIONS_FILE} "-D${def}\n")
endforeach()

