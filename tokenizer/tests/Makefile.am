#TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
#                  $(top_srcdir)/config/my-test-driver

TEST_EXTENSIONS = .sh
SH_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) ./my-test-driver


TESTS = \
	test_simple.sh \
    test_obj_array.sh \
    test_array_obj.sh

EXTRA_DIST = $(TESTS)

test : check

