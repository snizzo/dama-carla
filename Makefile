
rebuild:
	unlink server
	unlink client
	gcc -o server server.c
	gcc -o client client.c

build:
	gcc -o server server.c
	gcc -o client client.c network.c

clean:
	unlink server
	unlink client
