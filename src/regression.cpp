/*
 * Algav: Projet Arbre Huffman Adaptative
 * regression.cpp: pour tester que les fonctions font bien ce qu'on souhaite
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/arbre.hpp"
#include "../include/symbole.hpp"


int main (){

	Arbre *H;

	H=Arbre_creerVide();

	fprintf(stderr, "Arbre vide: %c %d\n", H->racine->caractere, H->racine->poids);

	fprintf(stderr, "On libère les structures allouées.\n");

	Arbre_detruire(H);

	return EXIT_SUCCESS;
}