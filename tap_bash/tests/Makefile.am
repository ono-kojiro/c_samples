
TESTS = \
	test_hoge.sh \
	test_foo.sh \
	simple.sh

TEST_EXTENSIONS = .sh

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/config/tap-driver.sh

SH_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/config/tap-driver.sh

test :
	$(MAKE) check

