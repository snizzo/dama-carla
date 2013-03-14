LIBSOURCES=network_data.c network.c filesystem.c auth.c
CC=clang
CFLAGS=-g -Weverything
all:
	$(CC) $(CFLAGS) -o client client.c $(LIBSOURCES)
	$(CC) $(CFLAGS) -o server server.c $(LIBSOURCES)
	$(CC) $(CFLAGS) -o logic logic.c

clean:
	rm client
	rm server
	rm logic
