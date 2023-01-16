check :
	ctest --output-junit junit_report.xml

test : check
	
clean-local :
	@if test -e "build.ninja"; then ninja clean; fi
	@rm -f junit_report.xml

