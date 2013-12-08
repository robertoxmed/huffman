/**
 * Algav: Projet Arbre Huffman Adaptative
 * compression.hpp: entêtes pour la compression et la décompression d'un texte
 *
 * Roberto MEDINA
 * 
 * 10 Décembre 2013
*/

#include "../include/compression.hpp"

int main(int argc, char ** argv){
	int fd_in, fd_out;
	
	if(argc != 4){
 		fprintf(stderr, "Usage %s -[cd] <fichier entrée> <fichier sortie>\n", argv[0]);
 		return EXIT_FAILURE;
 	}

	if(argv[1][0] != '-'){
		fprintf(stderr, "Usage %s -[cd] <fichier entrée> <fichier sortie>\n", argv[0]);
 		return EXIT_FAILURE;
	}
	
	if(argv[1][1] == 'c'){ //Quand on veut compresser un fichier
		if((fd_in = open(argv[2],O_RDONLY)) == -1){
			perror("open fd_in");
			exit(1);
		}
		if((fd_out = open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0600)) == -1){
			perror("open fd_out");
			exit(2);
		}
		
		Compression(fd_in,fd_out);

	}

	if(argv[1][1] == 'd'){ //Quand on veut decompresser un fichier
		if((fd_in = open(argv[2],O_RDONLY)) == -1){
			perror("open fd_in");
			exit(1);
		}
		if((fd_out = open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0600)) == -1){
			perror("open fd_out");
			exit(2);
		}
		
		Decompression(fd_in,fd_out);

	}

	

 	return EXIT_SUCCESS;
}
