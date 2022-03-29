all : m4 autoconf automake libtool

m4 :
	cd m4 && sh build.sh

autoconf :
	cd autoconf && sh build.sh

automake :
	cd automake && sh build.sh

libtool :
	cd libtool && sh build.sh

clean :
	cd m4 && sh build.sh clean
	cd autoconf && sh build.sh clean
	cd automake && sh build.sh clean
	cd libtool && sh build.sh clean

% :
	cd m4 && sh build.sh $*
	cd autoconf && sh build.sh $*
	cd automake && sh build.sh $*
	cd libtool && sh build.sh $*


check :
	sh check.sh

.PHONY : \
	all clean test \
	m4 autoconf automake libtool

