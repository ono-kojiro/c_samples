ACLOCAL_AMFLAGS = -I config

bin_PROGRAMS = txt2bin

txt2bin_SOURCES = \
	txt2bin.c

txt2bin_CFLAGS = \
	@LIBEVENT_CFLAGS@

txt2bin_LDADD = \
	@LIBEVENT_LIBS@

test :
	wget https://www.gnu.org/licenses/gpl-3.0.txt
	./txt2bin -o gpl-3.0.bin gpl-3.0.txt
	wget https://www.apache.org/licenses/LICENSE-2.0.txt
	./txt2bin -o apache-2.0.bin LICENSE-2.0.txt
	
	echo "Hello World" > header.txt
	./txt2bin -o header.bin header.txt
	echo "This is mux1." > mux1.txt
	./txt2bin -o mux1.bin -b 10 mux1.txt
	echo "This is mux2." > mux2.txt
	./txt2bin -o mux2.bin -b 20 mux2.txt
	echo "This is mux3." > mux3.txt
	./txt2bin -o mux3.bin -b 30 mux3.txt
	hexdump -C header.bin
	hexdump -C mux1.bin
	hexdump -C mux2.bin
	hexdump -C mux3.bin



