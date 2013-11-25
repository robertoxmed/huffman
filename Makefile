CC=clang++
CFLAGS=-Wall -pedantic -g
EXEC=huffman-regression
TAR=MedinaRoberto.huffman-dynamique

all: $(EXEC)

huffman-dynamique: obj/arbre.o obj/symbole.o obj/main.o
	$(CC) -o bin/huffman-dynamique obj/arbre.o obj/symbole.o obj/main.o $(CFLAGS);

huffman-regression: obj/arbre.o obj/symbole.o obj/regression.o
	$(CC) -o bin/huffman-regression obj/arbre.o obj/symbole.o obj/regression.o $(CFLAGS);

obj/main.o: src/main.cpp
	$(CC) -o obj/main.o -c src/main.cpp $(CFLAGS)

obj/regression.o: src/regression.cpp
	$(CC) -o obj/regression.o -c src/regression.cpp $(CFLAGS)

obj/arbre.o: src/arbre.cpp
	$(CC) -o obj/arbre.o -c src/arbre.cpp $(CFLAGS)

obj/symbole.o: src/symbole.cpp
	$(CC) -o obj/symbole.o -c src/symbole.cpp $(CFLAGS)