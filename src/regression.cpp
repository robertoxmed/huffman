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


	fprintf(stderr, "\nLe code de a : %s\n", Arbre_code(H,'a'));
	fprintf(stderr, "Le code de b : %s\n", Arbre_code(H,'b'));
	fprintf(stderr, "Le code de d : %s\n", Arbre_code(H,'d'));

	fprintf(stderr, "\n-------------------------------------------\n");
	fprintf(stderr, "-            Tests sur les symboles         -\n");
	fprintf(stderr, "---------------------------------------------\n\n");

	fprintf(stderr, "Affichage des Symboles:\n\n");

	Symbole *s_b = Symbole_init();
	Symbole *s_d = Symbole_init();
	Symbole_code_char(s_b,'b');
	fprintf(stderr, "Le code dans le buffer pour la lettre b : ");
	Symbole_printBinaire(s_b);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s_b->code, s_b->taille);

	char * code = Arbre_code(H,'d');
	Symbole_code(s_d,code,strlen(code));
	fprintf(stderr, "Le code dans le buffer pour la lettre d en prennant en compte l'arbre: ");
	Symbole_printBinaire(s_d);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s_d->code, s_d->taille);


	fprintf(stderr, "Est-ce que j'ai un 1 à la position 4: %d\n", Symbole_code_position(s_d->code,1));

	fprintf(stderr, "\nAffichage du Code buffer:\n\n");


	Code_buffer *cbf = Code_buffer_init();
	
	Code_buffer_transmettre(cbf,s_b);
	Code_buffer_transmettre(cbf,s_d);


	Code_buffer_printBinaire(cbf);


	fprintf(stderr, "On libère les structures allouées.\n");
	Symbole_detruire(s_b);
	Symbole_detruire(s_d);
	Arbre_detruire(H);


	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=               Fin des tests             =\n");
	fprintf(stderr, "===========================================\n\n");

	return EXIT_SUCCESS;
}
