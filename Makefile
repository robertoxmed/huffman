CC=clang++
CFLAGS=-Wall -pedantic -g
EXEC=huffman-regression huffman-dynamique
TAR=MedinaRoberto.huffman-dynamique

all: $(EXEC)

huffman-dynamique: obj/arbre.o obj/codage.o obj/compression.o obj/main.o
	$(CC) -o bin/huffman-dynamique obj/arbre.o obj/codage.o obj/compression.o obj/main.o $(CFLAGS);

huffman-regression: obj/arbre.o obj/codage.o obj/compression.o obj/regression.o
	$(CC) -o bin/huffman-regression obj/arbre.o obj/codage.o obj/compression.o obj/regression.o $(CFLAGS);

obj/main.o: src/main.cpp
	$(CC) -o obj/main.o -c src/main.cpp $(CFLAGS)

obj/regression.o: src/regression.cpp
	$(CC) -o obj/regression.o -c src/regression.cpp $(CFLAGS)

obj/compression.o: src/compression.cpp
	$(CC) -o obj/compression.o -c src/compression.cpp $(CFLAGS)

obj/arbre.o: src/arbre.cpp
	$(CC) -o obj/arbre.o -c src/arbre.cpp $(CFLAGS)

obj/codage.o: src/codage.cpp
	$(CC) -o obj/codage.o -c src/codage.cpp $(CFLAGS)

clean:
	rm -rf obj/*.o vgcore* bin/*

tar:
	tar -cvf - ../$(TAR) | gzip >../$(TAR).tgz

package: clean tar
	
