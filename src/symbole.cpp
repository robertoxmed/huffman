/*
 * Algav: Projet Arbre Huffman Adaptative
 * symbole.cpp: Pour l'implémentation de la manipulation des Symboles
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/symbole.hpp"

Symbole * Symbole_init(){
	Symbole * retour;
	retour = (Symbole *)malloc(sizeof(Symbole));
	retour->code=0;
	retour->taille=0;
	return retour;
}

Code * Code_init(){
	Code * retour;
	retour = (Code*)malloc(sizeof(Code));
	retour->code = (char*)malloc(2*sizeof(char));
	retour->taille = 0;
	return retour;
}

Code_buffer * Code_buffer_init(){
	Code_buffer * retour;
	retour = (Code_buffer*)malloc(sizeof(Code_buffer));
	retour->code_buffer = (char*)malloc(2*sizeof(char));
	retour->nb_bits = 0;
	retour->octet_courant = 0;
	retour->nb_octets = 0;
	return retour;
}



