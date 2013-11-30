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

int Noeud_est_frere(const Noeud *N, const Noeud *M){
	Noeud * Q = Noeud_get_pere(N);
	if(Noeud_get_filsGauche(Q) == M || Noeud_get_filsDroit(Q) == M)
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

Noeud * Noeud_get_feuille(Noeud *N, const unsigned char c){
	if(N->caractere == c)
		return N;
	else{
		Noeud_get_feuille(Noeud_get_filsDroit(N),c);
		Noeud_get_feuille(Noeud_get_filsDroit(N),c);
	}
	return NULL;
}

Noeud* Arbre_get_feuille(Arbre *H, const unsigned char c){
	return Noeud_get_feuille(H->racine,c);
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

Noeud* Arbre_get_feuilleSpeciale(Arbre *H){
	return H->feuilleSpeciale;
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
		Noeud_recherche_char(Noeud_get_filsDroit(N),c);
		Noeud_recherche_char(Noeud_get_filsGauche(N),c);
	}
	return 0;
}

int Arbre_recherche_char(Arbre *H, unsigned char c){
	return Noeud_recherche_char(H->racine,c);
}

Arbre* Arbre_Traitement(Arbre *H, Noeud *Q){
	return H;
}

Arbre* Arbre_Modification(Arbre *H, unsigned char c){
	Noeud *Q;
	if(!Arbre_recherche_char(H,c)){//Si le caractère n'est pas dans l'arbre
		//Allocation des nouveaux noeuds et affectation des valeurs
		Q = Noeud_get_pere(Arbre_get_feuilleSpeciale(H));
		Noeud *N_interne = Noeud_creerVide();
		N_interne->poids = 1;

		Noeud *N = Noeud_creerVide();
		Noeud_set_allValues(N,c,1);

		//Dynamique des pointeurs
		Noeud_set_allPointers(N,NULL,NULL,Noeud_get_suivant(Arbre_get_feuilleSpeciale(H)),
			Arbre_get_feuilleSpeciale(H),N_interne);

		Noeud_set_allPointers(N_interne,Arbre_get_feuilleSpeciale(H),N,NULL,NULL,Q);
		Q->filsGauche = N_interne;
		H->GDBH = N;
	}else{//Si le caractère est dans l'arbre
		Q = Arbre_get_feuille(H,c);
		if(Noeud_get_pere(Q)==Arbre_finBloc(H,Q) && 
			Noeud_est_frere(Arbre_get_feuilleSpeciale(H),Q) ){

			Q = Noeud_get_pere(Q);
		}
	}
	return Arbre_Traitement(H,Q);
}

Noeud* Arbre_finBloc(const Arbre *H, Noeud *N){
	unsigned int poids = Noeud_get_poids(N);
	Noeud *P = N;
	while(poids == Noeud_get_poids(P))
		P = P->suivant;
	return P;
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

void Noeud_affichage(const Noeud *N){
	if(N!=NULL){
		printf("( ");
		printf("%c - %d\n", Noeud_get_char(N), Noeud_get_poids(N));
		Noeud_affichage(Noeud_get_filsGauche(N));
		Noeud_affichage(Noeud_get_filsDroit(N));
		printf(") ");
	}
	
}

void Arbre_affichage(const Arbre *H){
	Noeud_affichage(H->racine);
}
