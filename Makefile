
build:
	gcc -o server server.c
	gcc -o client client.c

clean:
	unlink server
	unlink client
