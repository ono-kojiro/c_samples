bin_PROGRAMS = test_gperf

nodist_test_gperf_SOURCES = \
	options.c \
	userdata.c

BUILT_SOURCES = \
	options.c \
	userdata.c

CLEANFILES = \
	options.c \
	userdata.c

%.c : %.gperf Makefile
	gperf --no-strlen --output-file=$@ $<
	
test_gperf_SOURCES = \
	options.gperf \
	options.h \
	userdata.gperf \
	userdata.h \
	main.c

