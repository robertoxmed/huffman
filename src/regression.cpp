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

	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=  Tests de regression Huffman Dynamique  =\n");
	fprintf(stderr, "===========================================\n\n");

	//Création d'un arbre vide et on l'affiche
	H=Arbre_creerVide();
	fprintf(stderr, "Arbre vide: %c %d\n", H->racine->caractere, H->racine->poids);
	fprintf(stderr, "On test si c'est une feuille: %d\n", Noeud_estFeuille(H->racine));
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'b');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'r');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification_MAJ(H,'c');
	H = Arbre_Modification_MAJ(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification_MAJ(H,'d');
	Arbre_affichage(H);
	H = Arbre_Modification_MAJ(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification_MAJ(H,'b');//Problème iciii
	Arbre_affichage(H);
	H = Arbre_Modification_MAJ(H,'r');
	H = Arbre_Modification_MAJ(H,'a');
	Arbre_affichage(H);

	fprintf(stderr, "On libère les structures allouées.\n");
	Arbre_detruire(H);


	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=               Fin des tests             =\n");
	fprintf(stderr, "===========================================\n\n");

	return EXIT_SUCCESS;
}
