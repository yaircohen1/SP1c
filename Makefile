CC=gcc
FLAGS=-Wall -g

all: StrList

StrList: StrList.o Main.o
	$(CC) $(FLAGS) -o StrList StrList.o Main.o

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c

.PHONY: clean

clean:
	rm -f *.o StrList