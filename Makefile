
LIBSOURCES=network.c filesystem.c serverevents.c

build:
	clang -o server -g server.c $(LIBSOURCES) -Wall --pedantic -O0
	clang -o client -g client.c $(LIBSOURCES) -Wall --pedantic -O0

clean:
	unlink server
	unlink client
