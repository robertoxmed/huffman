/*
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.hpp: contient les entêtes pour les fonctions qui manipulent les arbres 
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#ifndef __ARBRE_
#define __ARBRE_

#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud_t {
	
	unsigned int poids;
	unsigned char caractere;

	Noeud_t *pere;

	Noeud_t *filsDroit;
	Noeud_t *filsGauche;


	Noeud_t *suivant;
	Noeud_t *precedant;

} Noeud;

struct Arbre_t
{
	Noeud *racine;
	Noeud *feuilleSpeciale;

	unsigned char caracteres[256];
};

typedef struct Arbre_t Arbre;

/*Initialise et alloue une structure dé noeud vide*/
Noeud* Noeud_creerVide();

/*Initialise et alloue la structure d'un arbre vide*/
Arbre* Arbre_creerVide();

/*Détruit un noeud*/
void Noeud_detruire(Noeud *N);

/*Détruit un arbre*/
void Arbre_detruire(Arbre *H);

//Renvoie vrai si le noeud est une feuille
int Noeud_estFeuille(Noeud *N);

Noeud* filsGauche(const Noeud *N);

Noeud* filsDroit(const Noeud *N);

Noeud* pere(const Noeud &N);

Noeud finBloc(const Arbre &H, const Noeud &N);


#endif
