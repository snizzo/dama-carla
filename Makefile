build:
	clang -o client client.c -Weverything
	clang -o server server.c -Weverything

clean:
	rm client
	rm server
