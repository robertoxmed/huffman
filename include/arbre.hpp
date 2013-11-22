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

	/*Ces pointeurs permettent de faire la vérification
	  de la propiété P */
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

/*Fonctions pour la gestion de la mémoire*/

//Initialise et alloue une structure dé noeud vide
Noeud* Noeud_creerVide();
//Initialise et alloue la structure d'un arbre vide
Arbre* Arbre_creerVide();
//Détruit un noeud
void Noeud_detruire(Noeud *N);
//Détruit un arbre
void Arbre_detruire(Arbre *H);
//Renvoie vrai si le noeud est une feuille
int Noeud_estFeuille(Noeud *N);

/*Liste d'accesseurs aux éléments du Noeuds*/

//Renvoie un pointeur sur le fils gauche du Noeud passé en argument
Noeud* Noeud_get_filsGauche(const Noeud *N);
//Renvoie un pointeur sur le fils droit du Noeud passé en argument
Noeud* Noeud_get_filsDroit(const Noeud *N);
//Renvoie un pointeur sur le père du Noeud passé en argument
Noeud* Noeud_get_pere(const Noeud *N);
//Renvoie un pointeur sur le suivant du Noeud
Noeud* Noeud_get_suivant(const Noeud *N);
//Renvoie un pointeur sur le précédant du Noeud
Noeud* Noeud_get_precedant(const Noeud *N);

/*Liste de mutateurs des éléments du Noeuds*/



/*Spécifique pour l'arbre de Huffman*/

Noeud* Noeud_finBloc(const Arbre &H, const Noeud &N);


//Affichage de l'arbre de Huffman
void Arbre_affichage(const Arbre *H);

#endif
