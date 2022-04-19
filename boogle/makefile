CC=gcc
CFLAGS=-ansi -pedantic -Wall

main: grille.o score.o partie.o fin_jeu.o ouverture.o affichage.o main.o
	$(CC) -o main main.o grille.o score.o partie.o fin_jeu.o ouverture.o affichage.o -lncurses

main.o: main.c score.h partie.h fin_jeu.h affichage.h ouverture.h grille.h
	$(CC) -c main.c $(CFLAGS)

grille.o: grille.c grille.h
	$(CC) -c grille.c $(CFLAGS)

score.o: score.c score.h partie.h
	$(CC) -c score.c $(CFLAGS)

partie.o: partie.c partie.h grille.h
	$(CC) -c partie.c $(CFLAGS)

fin_jeu.o: fin_jeu.c fin_jeu.h
	$(CC) -c fin_jeu.c $(CFLAGS)

ouverture.o: ouverture.c ouverture.h
	$(CC) -c ouverture.c $(CFLAGS)

affichage.o: affichage.c affichage.h grille.h
	$(CC) -c affichage.c $(CFLAGS)

clean:
	rm -f *.o
