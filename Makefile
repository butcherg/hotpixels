CC=g++
LIBRAW=/path/to/compiled/LibRaw

hotpixels: hotpixels.cpp
	$(CC) -ggdb -static -I$(LIBRAW) -o hotpixels hotpixels.cpp  $(LIBRAW)/build-w64/lib/.libs/libraw_r.a -lws2_32 -lz

clean:
	rm -rf hotpixels.exe

