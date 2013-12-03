/*
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.hpp: contient les entêtes pour les fonctions qui manipulent les arbres 
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#ifndef __SYMBOLE_
#define __SYMBOLE_

#include "arbre.hpp"

typedef struct Symbole_t{
	char code; //Octet qui contient le code du symbole
	int taille; //Combien de bits sont utilisés
	
} Symbole;

typedef struct Code_t{
	char * code; //Octets du code => ceci est utilisé pour la concaténation de la feuille spéciale
	int taille; //La taille finale après concaténation des deux symboles
} Code;

typedef struct Code_buffer_t{
	char * code_buffer; //La chaine de caractères qui code le texte
	int nb_bits; //Le nombre de bits écrits sur l'octet courrant
	int octet_courant; //Le nombre d'octets qui sont écrits actuellement
	int nb_octets; //Le nombre d'octets écrits en total
} Code_buffer;

//Fonctions d'initialisation des structures
Symbole * Symbole_init();
Code * Code_init();
Code_buffer * Code_buffer_init();

void Symbole_detruire(Symbole *s);
void Code_detruire(Code *c);
void Code_buffer_detruire(Code_buffer *cbf);

//Écrit le code en bits de la chaîne passée en paramètres et met à jour le nb de bits significatifs
void Symbole_code_char(Symbole *s, char * code, int taille);

//On crée une structure de code si on a plus de 8 bits de code
void Code_concatener(Code *cd, Symbole *s, Symbole *fs);

//On écrit un symbole sur le buffer
void Code_buffer_ecrireCode(Code_buffer *cbf, Symbole *s);

//On écrit le code dans le buffer qui va aller sur le fichier
void Code_buffer_ecrireCode(Code_buffer *cbf, Code *cd);

//On écrit sur le fichier le code final obtenu
void Code_buffer_fichier(Code_buffer * cbf, FILE * out);



#endif
