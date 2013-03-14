SOURCES=network_data.c network.c filesystem.c auth.c list.c
LIBS=-lncurses
CC=clang
CFLAGS=-g -Weverything
all:
	$(CC) $(CFLAGS) -o client client.c $(SOURCES) $(LIBS)
	$(CC) $(CFLAGS) -o server server.c $(SOURCES) $(LIBS)
	$(CC) $(CFLAGS) -o logic logic.c

clean:
	rm client
	rm server
	rm logic
