
CC=gcc
CFLAGS=-ansi -Wall

main: case.o position.o affichage.o menu.o partie.o  main.o
	$(CC) -o main main.o position.o case.o affichage.o menu.o partie.o -lncurses

main.o: main.c menu.h partie.h
	$(CC) -c main.c $(CFLAGS)

case.o: case.c case.h
	$(CC) -c case.c $(CFLAGS)

position.o: position.c position.h case.h
	$(CC) -c position.c $(CFLAGS)

affichage.o: affichage.c affichage.h position.h
	$(CC) -c affichage.c $(CFLAGS) 

menu.o: menu.c menu.h
	$(CC) -c menu.c $(CFLAGS)

partie.o: partie.c partie.h case.h position.h affichage.h
	$(CC) -c partie.c $(CFLAGS)

clean:
	rm -f *.o