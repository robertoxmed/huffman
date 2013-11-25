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

int Noeud_estFeuille(Noeud *N){
	if(N->filsDroit==NULL && N->filsGauche==NULL)
		return 1;
	return 0;
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

Noeud* Noeud_get_filsGauche(const Noeud *N){
	Noeud *retour;
	retour=N->filsGauche;
	return retour;
}
Noeud* Noeud_get_filsDroit(const Noeud *N){
	Noeud *retour;
	retour=N->filsDroit;
	return retour;
}
Noeud* Noeud_get_suivant(const Noeud *N){
	Noeud *retour;
	retour = N->suivant;
	return retour;
}
Noeud* Noeud_get_precedant(const Noeud *N){
	Noeud *retour;
	retour = N->precedant;
	return retour;
}
Noeud* Noeud_get_pere(const Noeud *N){
	Noeud *retour;
	retour = N->pere;
	return retour;
}
unsigned char Noeud_get_char(const Noeud *N){
	unsigned char c;
	c = N->caractere;
	return c;
}
unsigned int Noeud_get_poids(const Noeud *N){
	unsigned int p;
	p=N->poids;
	return p;
}

void Noeud_set_allPointers(Noeud *N, Noeud *fg, Noeud *fd,
	 Noeud *suivant, Noeud *precedant, Noeud * pere){
	if( N!= NULL){
		N->filsGauche = fg;
		N->filsDroit = fd;
		N->suivant = suivant;
		N->precedant = precedant;
		N->pere = pere;
	}
}

void Noeud_set_allValues(Noeud *N, const unsigned char c, const unsigned int p){
	if( N != NULL ){
		N->caractere = c;
		N->poids = p;
	}
}

int Noeud_recherche_char(Noeud *N, unsigned char c){
	if(Noeud_get_char(N)==c)
		return 1;
	else{
		Noeud_recherche_char(N->fd,c);
		Noeud_recherche_char(N->fg,c);
	}
	return 0;
}

int Arbre_recherche_char(Arbre *H, unsigned char c){
	return Noeud_recherche_char(H->racine);
}

Arbre* Arbre_Traitement(Arbre *H, Noeud *Q){

}

Arbre* Arbre_Modification(Arbre *H, unsigned char c){
	Noeud *Q;
	if(!Arbre_recherche_char(H,c)){
		Q = Noeud_get_pere(Arbre_get_feuilleSpeciale(H));
		Noeud *N = Noeud_creerVide();
		Noeud_set_allValues(c,1);
		Noeud_set_allPointers();
	}else{
		Q = Arbre_get_feuille(H,c);
		if(Noeud_get_pere(Q)==Arbre_finBloc(H,Q) && 
			Noeud_est_frere(Arbre_get_feuilleSpeciale(H),Q) ){

			Q = Noeud_get_pere(Q);
		}
	}
	return Arbre_Traitement(H,Q);
}



unsigned char Noeud_code(const Noeud *N){
	if(Noeud_get_filsDroit( Noeud_get_pere(N) ) == N)//Si c'est le fils droit
		return '1';
	else
		return '0';
}

unsigned char * Arbre_code(const Arbre *H, Noeud *N){
	Noeud *tmp;
	tmp = N;
	unsigned char *code, buff[50];
	int i = 0;

	while (tmp!=H->racine){
		buff[i]=Noeud_code(tmp);
		i++;
	}
	buff[i]='\0';
	code = (unsigned char *)malloc(i*sizeof(unsigned char));
	//On inverse le code
	for(int j=0;j<i;j++){
		code[j]=buff[i-1];
		i--;
	}
	return code;
}
