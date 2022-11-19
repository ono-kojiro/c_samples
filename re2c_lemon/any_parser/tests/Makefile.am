#TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
#                  $(top_srcdir)/config/my-test-driver

TEST_EXTENSIONS = .sh
SH_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) ./my-test-driver


TESTS = \
	test_simple.sh \
    test_alphabet.sh \
    test_digits.sh \
    test_hex.sh

EXTRA_DIST = $(TESTS)

test : check

