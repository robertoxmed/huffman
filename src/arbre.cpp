/*
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.cpp: Pour l'implémentation de la manipulation des arbres de Huffman
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/arbre.hpp"

Noeud* Noeud_creerVide(){
	Noeud * retour;
	retour = (Noeud*)malloc(sizeof(Noeud));
	/*On initialise la structure*/
	retour->poids = 0;
	retour->caractere = ' ';
	retour->pere = NULL;
	retour->filsDroit = NULL;
	retour->filsGauche = NULL;
	retour->suivant = NULL;
	retour->precedant = NULL;

	return retour;
}

Arbre* Arbre_creerVide(){
	Arbre *H = (Arbre*)malloc(sizeof(Arbre));
	/*Au début la racine est la feuille spéciale*/
	H->feuilleSpeciale = Noeud_creerVide();
	H->racine = H->feuilleSpeciale;
	H->feuilleSpeciale->caractere = '#';
	H->feuilleSpeciale->poids = 0; /*La feuille spéciale a toujours un poids de 0*/

	for(int i=0; i<256; i++){
		H->caracteres[i] = 0;
	}

	return H;
}

void Noeud_detruire(Noeud *N){
	if(N!=NULL && !Noeud_estFeuille(N)){
		/*On libère que les fils et pas les voisins*/
		Noeud_detruire(N->filsGauche);
		Noeud_detruire(N->filsDroit);
		free(N);
	}else if (Noeud_estFeuille(N)){
		free(N);
	}else{
		fprintf(stderr, "On essaye de détruire un noeud non alloué.\n");
		exit(1);
	}
}

void Arbre_detruire(Arbre *H){
	if(H!=NULL){
		Noeud_detruire(H->racine);
		free(H);
	}else{
		fprintf(stderr, "On essaye de détruire un arbre non alloué.\n");
		exit(1);
	}
}

int Noeud_estFeuille(Noeud *N){
	return N->filsDroit==NULL && N->filsGauche==NULL;
}

