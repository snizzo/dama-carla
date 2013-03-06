LIBSOURCES=network_data.c
CFLAGS=-g -Weverything
all:
	clang $(CFLAGS) -o client client.c $(LIBSOURCES)
	clang $(CFLAGS) -o server server.c $(LIBSOURCES)

clean:
	rm client
	rm server
