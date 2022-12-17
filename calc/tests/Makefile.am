LOG_DRIVER := $(SHELL) test_wrapper $(top_srcdir)/config/test-driver

EXTRA_DIST = 01-mycalc_test.sh

TESTS = 01-mycalc_test.sh

check_SCRIPTS = 01-mycalc_test.sh

check : junit_result.xml

junit_result.xml : $(TEST_LOGS:.log=.trs)
	python3 trs2junit.py -o $@ $(TEST_LOGS:.log=.trs)

