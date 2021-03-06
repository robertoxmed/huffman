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

/*------------------------------------------
		Les différentes structures
		pour le codage et le decodage
----------------------------------------------*/

typedef struct Code_Symbole_t{
	char code; //Octet qui contient le code du symbole
	int taille; //Combien de bits sont utilisés
	
} Code_Symbole;

typedef struct Code_buffer_t{
	char code_buffer[5000]; //La chaine de caractères qui code le texte
	int nb_bits; //Le nombre de bits écrits sur l'octet courrant
	int octet_courant; //Le nombre d'octets qui sont écrits actuellement
	int nb_octets; //Le nombre d'octets écrits en total
} Code_buffer;

typedef struct Decode_buffer_t{
	char decode_buffer[5000]; //Le texte compressé
	int position_bit; //Position du prochain bit à lire
	int octet_courant; //Pour se reperer dans le buffer du texte compressé
} Decode_buffer;

/*------------------------------------------
		Fonctions d'initialisation et
		destruction des structures
----------------------------------------------*/

Code_Symbole * Code_Symbole_init();

Code_buffer * Code_buffer_init();

Decode_buffer * Decode_buffer_init();

void Code_Symbole_detruire(Code_Symbole *s);

void Code_buffer_detruire(Code_buffer *cbf);

void Decode_buffer_detruire(Decode_buffer *dbf);

/*------------------------------------------
		Fonctions utilitaire pour
				le codage
----------------------------------------------*/

//Ecrit le code en bits du caractère c
void Code_Symbole_code_char(Code_Symbole *s, char c);

//Écrit le code en bits de la chaîne passée en paramètres et met à jour le nb de bits significatifs
void Code_Symbole_code(Code_Symbole *s, char * code, int taille);

//Affiche le code binaire d'un symbole avec la taille
void Code_Symbole_printBinaire(const Code_Symbole *s);

//Renvoie vrai si on a un bit à 1 à la position passée en paramètre
int Code_Symbole_code_position(const char c, const int position);

//On écrit un symbole sur le buffer
void Code_buffer_transmettre(Code_buffer *cbf, Code_Symbole *s);

//Affiche en binaire le code buffer qui va aller sur le fichier après compression
void Code_buffer_printBinaire(const Code_buffer *cbf);

int Code_get_nb_char(const Code_buffer *cbf);

/*------------------------------------------
		Fonctions utilitaire pour
				le decodage
----------------------------------------------*/

//Décale la position de un et decale dans le buffer si besoin
void Decode_Next(Decode_buffer * dbf);

//Renvoie un si le prochain bit est à 1
int Decode_get_Next(Decode_buffer *dbf);

//Renvoie le caractère
char Decode_getLettre(Decode_buffer *dbf);

#endif
