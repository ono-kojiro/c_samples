all : init gen test

gen :
	sh generate.sh

init :
	shellspec --init

check : test

test :
	@shellspec -f junit --reportdir . --output junit --quiet

mclean :
	rm -rf .shellspec
	rm -rf spec/

