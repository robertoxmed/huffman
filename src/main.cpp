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

	if(argc != 4){
 		fprintf(stderr, "Usage %s -[cd] <fichier entrée> <fichier sortie>\n", argv[0]);
 		return EXIT_FAILURE;
 	}

 	return EXIT_SUCCESS;
}
