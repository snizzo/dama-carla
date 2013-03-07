LIBSOURCES=network_data.c network.c
CFLAGS=-g -Weverything
all:
	clang $(CFLAGS) -o client client.c $(LIBSOURCES)
	clang $(CFLAGS) -o server server.c $(LIBSOURCES)
	clang $(CFLAGS) -o logic logic.c

clean:
	rm client
	rm server
	rm logic
