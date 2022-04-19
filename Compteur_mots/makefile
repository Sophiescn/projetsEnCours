CC=gcc
CFLAGS=-ansi -pedantic -Wall

clm: ouverture.o transformation.o main.o test.o option.o
	$(CC) -o clm main.o ouverture.o transformation.o option.o test.o

main.o: main.c ouverture.h transformation.h test.h
	$(CC) -c main.c $(CFLAGS)

ouverture.o: ouverture.c ouverture.h
	$(CC) -c ouverture.c $(CFLAGS)

transformation.o: transformation.c transformation.h
	$(CC) -c transformation.c $(CFLAGS)

option.o: option.c option.h transformation.h
	$(CC) -c option.c $(CFLAGS)

test.o: test.c test.h ouverture.h transformation.h option.h
	$(CC) -c test.c $(CFLAGS)

clean:
	rm -f *.o
