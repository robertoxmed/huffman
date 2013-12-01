/*
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.cpp: Pour l'implémentation de la manipulation des arbres de Huffman
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/arbre.hpp"

using namespace std;

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

	return retour;
}

Arbre* Arbre_creerVide(){
	Arbre *H = (Arbre*)malloc(sizeof(Arbre));
	/*Au début la racine est la feuille spéciale*/
	H->feuilleSpeciale = Noeud_creerVide();
	H->racine = H->feuilleSpeciale;
	H->feuilleSpeciale->caractere = '#';
	H->feuilleSpeciale->poids = 0; /*La feuille spéciale a toujours un poids de 0*/
	H->feuilleSpeciale->pere = H->feuilleSpeciale;

	H->premiere_insertion = 1;

	return H;
}

int Noeud_estFeuille(Noeud *N){
	if(N->filsDroit==NULL && N->filsGauche==NULL && N->caractere!='#')
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
	if(N!=NULL){
		/*On libère que les fils et pas les voisins*/
		Noeud_detruire(N->filsGauche);
		Noeud_detruire(N->filsDroit);
		free(N);
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
	 Noeud *suivant, Noeud * pere){
	if( N!= NULL){
		N->filsGauche = fg;
		N->filsDroit = fd;
		N->suivant = suivant;
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
	if(N!=NULL){
		if(Noeud_get_char(N)==c)
			return 1;
		else{
			Noeud_recherche_char(Noeud_get_filsDroit(N),c);
			Noeud_recherche_char(Noeud_get_filsGauche(N),c);
		}
	}
	return 0;
}

int Arbre_recherche_char(Arbre *H, unsigned char c){
	return Noeud_recherche_char(H->racine,c);
}


int compare (const void * a, const void * b){
  return ( Noeud_get_poids((Noeud*)a) - Noeud_get_poids((Noeud*)b) );
}

void Noeud_recup_Noeuds(Noeud *N, vector<Noeud*> v){
	if(N!=NULL){
		v.push_back(N);
		Noeud_recup_Noeuds(Noeud_get_filsGauche(N),v);
		Noeud_recup_Noeuds(Noeud_get_filsDroit(N),v);	
	}
}

void Arbre_maj_pointeurSuivant(Arbre *H){
	//Stocker les feuilles dans un vecteur
	vector<Noeud*> v_feuilles;

	Noeud_recup_Noeuds(H->racine,v_feuilles);
	//Tri des feuilles
	sort(v_feuilles.begin(),v_feuilles.end(),compare);

	//MAJ du pointeur suivant
	for(int i=0;i<v_feuilles.size()-1;i++){
		Noeud_set_allPointers(v_feuilles[i],Noeud_get_filsGauche(v_feuilles[i]),Noeud_get_filsDroit(v_feuilles[i]),
			v_feuilles[i+1],Noeud_get_pere(v_feuilles[i]));
	}
	Noeud_set_allPointers(v_feuilles[v_feuilles.size()],Noeud_get_filsGauche(v_feuilles[v_feuilles.size()]),Noeud_get_filsDroit(v_feuilles[v_feuilles.size()]),
			NULL,Noeud_get_pere(v_feuilles[v_feuilles.size()]));
}

//Change la structure de l'arbre => va falloir mettre à jour les pointeurs sur suivant
void Noeud_echanger(Arbre *H, Noeud *N,Noeud* M){ 
	Noeud *Q = Noeud_get_pere(N);
	Noeud *P = Noeud_get_pere(M);

	if(Noeud_get_filsGauche(Q) == N){

		Noeud_set_allPointers(Q,M,Noeud_get_filsDroit(Q),
			Noeud_get_suivant(Q),Noeud_get_pere(Q));

		if(Noeud_get_filsGauche(P) == M){
			Noeud_set_allPointers(P,N,Noeud_get_filsDroit(Q),
				Noeud_get_suivant(Q),Noeud_get_pere(Q));

		}else{
			Noeud_set_allPointers(P,Noeud_get_filsGauche(Q),N,
				Noeud_get_suivant(Q),Noeud_get_pere(Q));
		}
	}else{
		Noeud_set_allPointers(Q,Noeud_get_filsGauche(Q),M
			,Noeud_get_suivant(Q),Noeud_get_pere(Q));

		if(Noeud_get_filsGauche(P) == M){
			Noeud_set_allPointers(P,N,Noeud_get_filsDroit(Q),
				Noeud_get_suivant(Q),Noeud_get_pere(Q));
		}else{
			Noeud_set_allPointers(P,Noeud_get_filsGauche(Q),N,
				Noeud_get_suivant(Q),Noeud_get_pere(Q));
		}
	}
}

Arbre* Arbre_Traitement(Arbre *H, Noeud *Q){
	vector<Noeud*> Gamma_Q; //Le chemin à la racine
	vector<int> Gamma_x;
	Noeud *P = Q;
	int echanger = 0;
	int indice;

	if(P == H->racine){
		Gamma_Q.push_back(P);
		Gamma_x.push_back(Noeud_get_poids(P));
	}else{
		while(P != H->racine){
			Gamma_Q.push_back(P);
			Gamma_x.push_back(Noeud_get_poids(P));
			P = Noeud_get_pere(P);
		}
		Gamma_Q.push_back(P);
		Gamma_x.push_back(Noeud_get_poids(P));
	}

	//Parcourir les valeurs de Gamma_Q, verifier P
	if(Gamma_x.size()!=1){
		for(int i=0;i<Gamma_x.size()-1;i++){
			if(Gamma_x[i]>=Noeud_get_poids(Noeud_get_suivant(Gamma_Q[i]))){
				echanger = 1;
				indice = i;
				break;
			}
		}
	}
	
	if(echanger == 0){ //Si P satisfaite on incrémente les poids
		for(int i=0;i<Gamma_x.size();i++){
			Gamma_Q[i]->poids++;
		}	
	}else{	//Sinon echanger apres avoir incrémenté les incrémentables
		Noeud *m = Gamma_Q[indice];
		Noeud *b = Arbre_finBloc(H,m);

		for(int i=0;i<indice;i++){
			Gamma_Q[i]->poids++;
		}
		Noeud_echanger(H,b,m);
		m->poids++;
		return(Arbre_Traitement(H,Noeud_get_pere(m)));
	}
	return H;
}

Arbre* Arbre_Modification(Arbre *H, unsigned char c){
	Noeud *Q;
	if(H->premiere_insertion){
		//La première insertion est un peu spéciale
		Noeud *N_interne = Noeud_creerVide();
		N_interne->poids = 1;

		Noeud *N = Noeud_creerVide();
		Noeud_set_allValues(N,c,1);

		//Dynamique des pointeurs
		Noeud_set_allPointers(Arbre_get_feuilleSpeciale(H),NULL,NULL,
			N,N_interne);

		Noeud_set_allPointers(N,NULL,NULL,
			N_interne,N_interne);

		Noeud_set_allPointers(N_interne,Arbre_get_feuilleSpeciale(H),N,
			NULL,N_interne);
		H->racine = N_interne;
		H->premiere_insertion = 0;
		return H;

	}else if(!Arbre_recherche_char(H,c)){//Si le caractère n'est pas dans l'arbre
		//Allocation des nouveaux noeuds et affectation des valeurs
		Q = Noeud_get_pere(Arbre_get_feuilleSpeciale(H));
		Noeud *N_interne = Noeud_creerVide();
		N_interne->poids = 1;

		Noeud *N = Noeud_creerVide();
		Noeud_set_allValues(N,c,1);

		//Dynamique des pointeurs
		Q->filsGauche = N_interne;
		Noeud_set_allPointers(N_interne,Arbre_get_feuilleSpeciale(H),N,
			Noeud_get_filsDroit(Q),Q);

		Noeud_set_allPointers(N,NULL,NULL,
			Noeud_get_suivant(Arbre_get_feuilleSpeciale(H)),N_interne);

		Noeud_set_allPointers(Arbre_get_feuilleSpeciale(H),NULL,NULL,
			N,N_interne);

		return Arbre_Traitement(H,Q);

	}else{//Si le caractère est dans l'arbre
		Q = Arbre_get_feuille(H,c);
		if(Noeud_get_pere(Q)==Arbre_finBloc(H,Q) && 
			Noeud_est_frere(Arbre_get_feuilleSpeciale(H),Q) ){

			Q = Noeud_get_pere(Q);
		}
		return Arbre_Traitement(H,Q);
	}
}

Arbre * Arbre_Modification_MAJ(Arbre *H, unsigned char c){
	H = Arbre_Modification(H,c);
	Arbre_maj_pointeurSuivant(H);
	return H;
}

Noeud* Arbre_finBloc(const Arbre *H, Noeud *N){
	unsigned int poids = Noeud_get_poids(N);
	Noeud *P = N->suivant;
	Noeud *Q;
	if(Noeud_get_poids(P)>poids)
		return N;
	
	while(poids == Noeud_get_poids(P) && P->suivant!=NULL){
		Q = P;
		P = P->suivant;

	}
	return Q;
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
		fprintf(stderr," { ");
		fprintf(stderr,"[%c - %d]", Noeud_get_char(N), Noeud_get_poids(N));
		Noeud_affichage(Noeud_get_filsGauche(N));
		Noeud_affichage(Noeud_get_filsDroit(N));
		fprintf(stderr," } ");
	}
	
}

void Arbre_affichage(const Arbre *H){
	Noeud_affichage(H->racine);
	fprintf(stderr, "\n");
}
