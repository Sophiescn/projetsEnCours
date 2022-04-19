CC=gcc
CFLAGS=-ansi -pedantic -Wall -lncurses

main: case.o graphique.o monde.o pomme.o serpent.o sauvegarde.o main.o
	$(CC) -o main main.o case.o graphique.o monde.o pomme.o serpent.o sauvegarde.o $(CFLAGS)

main.o: main.c case.h graphique.h monde.h pomme.h serpent.h sauvegarde.h
	$(CC) -c main.c $(CFLAGS)

case.o: case.c case.h
	$(CC) -c case.c $(CFLAGS)

graphique.o: graphique.c graphique.h monde.h case.h serpent.h pomme.h sauvegarde.h
	$(CC) -c graphique.c $(CFLAGS)

monde.o: monde.c monde.h serpent.h pomme.h case.h sauvegarde.h
	$(CC) -c monde.c $(CFLAGS)

pomme.o: pomme.c pomme.h case.h
	$(CC) -c pomme.c $(CFLAGS)

serpent.o: serpent.c serpent.h case.h 
	$(CC) -c serpent.c $(CFLAGS)

sauvegarde.o: sauvegarde.c sauvegarde.h monde.h
	$(CC) -c sauvegarde.c $(CFLAGS)

clean:
	rm -f *.o
