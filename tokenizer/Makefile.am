ACLOCAL_AMFLAGS = -I config

SUBDIRS = tools/re2c

if USE_PARSER
SUBDIRS += tools \
    parser
endif

SUBDIRS += \
	scanner \
	example \
	tests

test :
	$(MAKE) check

