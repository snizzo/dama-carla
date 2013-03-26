SOURCES=network_data.c network.c filesystem.c auth.c list.c interface.c logic.c
LIBS=-lncurses -lform
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

server:
	$(CC) $(CFLAGS) -o server server.c $(SOURCES) $(LIBS)

client:
	$(CC) $(CFLAGS) -o client client.c $(SOURCES) $(LIBS)

