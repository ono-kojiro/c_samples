ACLOCAL_AMFLAGS = -I config

SUBDIRS =

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

