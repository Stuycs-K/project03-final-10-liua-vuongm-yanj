compile: clientexe serverexe

clientexe: client.o networking.o semaphore.o
	@gcc -o clientexe client.o networking.o semaphore.o

serverexe: server.o networking.o semaphore.o
	@gcc -o serverexe server.o networking.o semaphore.o

client.o: client.c networking.h semaphore.h client.h
	@gcc -c client.c

server.o: server.c networking.h semaphore.h
	@gcc -c server.c

networking.o: networking.c networking.h
	@gcc -c networking.c

semaphore.o: semaphore.c semaphore.h
	@gcc -c semaphore.c

client: clientexe
	@./clientexe

server: serverexe
	@./serverexe

clean:
	@rm -f *.o
	@rm -f *~
	@rm -f serverexe
	@rm -f clientexe
	@rm -f *.txt
