ACLOCAL_AMFLAGS = -I config

bin_PROGRAMS = txt2bin

txt2bin_SOURCES = \
	txt2bin.c

txt2bin_CFLAGS = \
	@LIBEVENT_CFLAGS@

txt2bin_LDADD = \
	@LIBEVENT_LIBS@

test :
	echo "Hello World" > header.txt
	./txt2bin -o header.bin header.txt
	echo "abcdefgabcdefg." > mux1.txt
	./txt2bin -o mux1.bin -b 10 mux1.txt
	echo "hijklmnhijklmn." > mux2.txt
	./txt2bin -o mux2.bin -b 20 mux2.txt
	echo "opqrstuopqrstu." > mux3.txt
	./txt2bin -o mux3.bin -b 30 mux3.txt
	hexdump -C header.bin
	hexdump -C mux1.bin
	hexdump -C mux2.bin
	hexdump -C mux3.bin



