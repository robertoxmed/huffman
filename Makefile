CC=clang++
CFLAGS=-Wall -ansi -pedantic -g
EXEC=huffman-dynamique
TAR=MedinaRoberto.huffman-dynamique

all: $(EXEC)

huffman-dynamique: obj/arbre.o obj/symbole.o obj/main.o
	$(CC) -o bin/huffman-dynamique obj/arbre.o obj/symbole.o $(CFLAGS);

obj/main.o: src/main.cpp

obj/arbre.o: src/arbre.o
	$(CC)