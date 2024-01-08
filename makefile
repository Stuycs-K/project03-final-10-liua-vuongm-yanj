compile: client server

client: client.o networking.o semaphore.o
	@gcc -o client client.o networking.o semaphore.o

server: server.o networking.o semaphore.o
	@gcc -o server server.o networking.o semaphore.o

client.o: client.c networking.h semaphore.h
	@gcc -c client.c

server.o: server.c networking.h semaphore.h
	@gcc -c server.c

networking.o: networking.c networking.h
	@gcc -c networking.c

semaphore.o: semaphore.c semaphore.h
	@gcc -c semaphore.c

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f server
	@rm -f client
