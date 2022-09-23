project(chapter_12)

set(CHAPTER_DIR "${CMAKE_SOURCE_DIR}/work/sources/Chapter_12")

add_executable(server-libevent
	${CHAPTER_DIR}/server-libevent.c
)

target_link_libraries(server-libevent
	PUBLIC -levent
)

add_executable(server-afindepend
	${CHAPTER_DIR}/server-afindepend.c
)


bison_target(MyParser
  ${CHAPTER_DIR}/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
  COMPILE_FLAGS -d
)
flex_target(MyScanner
  ${CHAPTER_DIR}/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

add_flex_bison_dependency(MyScanner MyParser)

add_executable(client-2
	${CHAPTER_DIR}/client-2.c
	${BISON_MyParser_OUTPUTS}
	${FLEX_MyScanner_OUTPUTS}
)


target_link_libraries(client-2 ${FLEX_LIBRARIES})




