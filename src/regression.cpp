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

	fprintf(stderr, "\n-------------------------------------------\n");
	fprintf(stderr, "=            Tests sur les arbres           =\n");
	fprintf(stderr, "----------------------------------------------\n\n");
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
	H = Arbre_Modification(H,'c');
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'d');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'b');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'r');
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);


	fprintf(stderr, "Le code de a : %s\n", Arbre_code(H,'a'));
	fprintf(stderr, "Le code de b : %s\n", Arbre_code(H,'b'));
	fprintf(stderr, "Le code de d : %s\n", Arbre_code(H,'d'));

	fprintf(stderr, "\n-------------------------------------------\n");
	fprintf(stderr, "-            Tests sur les symboles         -\n");
	fprintf(stderr, "---------------------------------------------\n\n");

	fprintf(stderr, "Affichage des Symboles:\n\n");

	Symbole *s = Symbole_init();
	Symbole_code_char(s,'b');
	Symbole_printBinaire(s);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s->code, s->taille);

	char * code = Arbre_code(H,'d');
	Symbole_code(s,code,strlen(code));
	Symbole_printBinaire(s);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s->code, s->taille);


	fprintf(stderr, "Est-ce que j'ai un 1 à la position 0: %d\n", Symbole_code_position(s->code,0));

	fprintf(stderr, "\nAffichage du Code buffer:\n\n");


	Code_buffer *cbf = Code_buffer_init();
	Code_buffer_ecrireSymbole(cbf,s);

	Code_buffer_printBinaire(cbf);


	fprintf(stderr, "On libère les structures allouées.\n");
	Symbole_detruire(s);
	Arbre_detruire(H);


	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=               Fin des tests             =\n");
	fprintf(stderr, "===========================================\n\n");

	return EXIT_SUCCESS;
}
