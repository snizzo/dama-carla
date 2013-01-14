
LIBSOURCES=network.c parser.c filesystem.c

rebuild:
	unlink server
	unlink client
	clang -o server server.c $(LIBSOURCES)
	clang -o client client.c $(LIBSOURCES)

build:
	clang -o server server.c $(LIBSOURCES)
	clang -o client client.c $(LIBSOURCES)

clean:
	unlink server
	unlink client
