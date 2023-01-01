JUNIT_REPORT = junit_report.xml

all : xsd merge

xsd : junit-10.xsd

junit-10.xsd :
	curl -O -L https://raw.githubusercontent.com/jenkinsci/xunit-plugin/master/src/main/resources/org/jenkinsci/plugins/xunit/types/model/xsd/junit-10.xsd

merge :
	rm -f $(JUNIT_REPORT)
	./merge_junitxml.py -o $(JUNIT_REPORT)

clean :
	rm -f $(JUNIT_REPORT)


