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
#include <string.h>
#include <vector>

/* --------------------------------------------
	Définitions des structures de données
 ----------------------------------------------*/ 

typedef struct Noeud_t {
	
	unsigned int poids;
	unsigned char caractere;

	Noeud_t *pere;

	Noeud_t *filsDroit;
	Noeud_t *filsGauche;

	//Ce pointeur et entier permettent vérifier la propiété GDBH
	Noeud_t *suivant;
	Noeud_t *precedant; //On a une liste doublement chaînée

} Noeud;

typedef struct Arbre_t
{
	Noeud *racine;
	Noeud *feuilleSpeciale;
	
	int premiere_insertion;
	char caracteres[256]; //Tableau qui contient les caractères de l'abre

} Arbre;

/*----------------------------------------
	Fonctions pour la gestion de la mémoire
-----------------------------------------*/

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

/*-----------------------------------------
	Liste d'accesseurs aux éléments du Noeuds
------------------------------------------*/

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
//Renvoie le caractère du Noeud
unsigned char Noeud_get_char(const Noeud *N);
//Renvoie le poids du Noeud
unsigned int Noeud_get_poids(const Noeud *N);

/*------------------------------------------
	Liste de mutateurs des éléments du Noeuds
-------------------------------------------*/

//Pour initialiser tous les pointeurs du Noeud N
void Noeud_set_allPointers(Noeud *N, Noeud *fg, Noeud *fd,
	 Noeud *suivant, Noeud *precedant, Noeud * pere);
//Pour initialiser les valeurs du Noeud N
void Noeud_set_allValues(Noeud *N, unsigned char c, unsigned int p);


/*-----------------------------------------
	Spécifique pour l'arbre de Huffman
------------------------------------------*/

//Fonction de modification de l'arbre de Huffman. On va rajouter le caractère c
Arbre* Arbre_Modification(Arbre *H, unsigned char c);

//Fonction de Traitement de l'arbre de Huffman
Arbre* Arbre_Traitement(Arbre *H, Noeud *Q);

//Retourne le code correspondant au caractère c
char * Arbre_code(Arbre *H, unsigned char c);

//Retourne le code correspondant à la feuille spéciale
char * Arbre_code_FS(Arbre *H);

//Va echanger la possition des deux Noeuds
void Noeud_echanger(Arbre *H, Noeud *N, Noeud *M);

//Retourne le premier Noeud qui n'a pas le même poids que N
Noeud* Arbre_finBloc(const Arbre *H, Noeud *N);

//Affichage de l'arbre de Huffman
void Arbre_affichage(const Arbre *H);

//Recherche un caractère dans l'arbre de Huffman
int Arbre_recherche_char(Arbre *H, unsigned char c);


#endif
