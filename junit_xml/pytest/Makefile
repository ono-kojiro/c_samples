PYTEST = pytest-3

JUNIT_XML = junit_report.xml

all : junit

junit :
	$(PYTEST) test_prime.py --junitxml=tmp.xml
	xmllint --format tmp.xml > $(JUNIT_XML)
	rm -f tmp.xml

clean :
	rm -f $(JUNIT_XML)

