CFLAGS=-std=c99 -O3 -g3 -D_POSIX_SOURCE
PREFIX?=/usr/local/

all:trim

install: trim
	install -D trim "${PREFIX}/bin/"

clean:
	rm -f trim
