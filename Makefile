CC=gcc
CFLAGS=-c -Wall

all: client server

create_server.o: create_server.c
	$(CC) $(CFLAGS) create_server.c

create_client.o: create_client.c
	$(CC) $(CFLAGS) create_client.c

server.o: server.c
	$(CC) $(CFLAGS) server.c

client.o: client.c
	$(CC) $(CFLAGS) client.c

log.o: log.c
	$(CC) $(CFLAGS) log.c

server: create_server.o server.o log.o
	$(CC) create_server.o server.o log.o -o server

client: create_client.o client.o log.o
	$(CC) create_client.o client.o log.o -o client

clean:
	rm -rf server client
