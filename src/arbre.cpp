/**
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.cpp: définit les fonctions de gestion de l'arbre
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
	retour->caractere = '_';
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
	H->feuilleSpeciale->pere = H->feuilleSpeciale;

	H->premiere_insertion = 1;
	memset(H->caracteres,0,sizeof(H->caracteres));
	H->nb_caracteres = 0;

	return H;
}

int Noeud_estFeuille(Noeud *N){
	if(N->filsDroit==NULL && N->filsGauche==NULL )
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
void Noeud_affichage(const Noeud *N){
	fprintf(stderr,"[%c - %d]", Noeud_get_char(N), Noeud_get_poids(N));
}

Noeud * Noeud_get_feuille(Noeud *N, const unsigned char c){
	Noeud *Q = NULL;
	if(N!=NULL){
		if(Noeud_estFeuille(N) && Noeud_get_char(N) == c){
			Q = N;
			return Q;
		}else{
			Q = Noeud_get_feuille(Noeud_get_filsGauche(N),c);
			if(Q!=NULL)
				return Q;
			else
				Q = Noeud_get_feuille(Noeud_get_filsDroit(N),c);
		}
	}
	return Q;
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

int Arbre_recherche_char(Arbre *H, unsigned char c){
	for(int i=0;i<H->nb_caracteres;i++){
		if(H->caracteres[i] == c)
			return 1;
	}
	return 0;
}

//Change la structure de l'arbre => va falloir mettre à jour les pointeurs sur suivant
void Noeud_echanger(Arbre *H, Noeud *N, Noeud* M){ 
	Noeud *Q = Noeud_get_pere(N);
	Noeud *P = Noeud_get_pere(M);
	Noeud *suivantTmp, *precedantTmp;

	//Dynamique sur l'arbre
	if(Noeud_get_filsGauche(Q) == N){
		Q->filsGauche = M;
		M->pere = Q;
		if(Noeud_get_filsGauche(P) == M){
			P->filsGauche = N;
			N->pere = P;
		}else{
			P->filsDroit = N;
			N->pere = P;
		}
	}else{
		Q->filsDroit = M;
		M->pere = Q;
		if(Noeud_get_filsGauche(P) == M){
			P->filsGauche = N;
			N->pere = P;
		}else{
			P->filsDroit = N;
			N->pere = P;
		}
	}
	
	//Dynamique sur la liste doublement chaînée
	suivantTmp = N->suivant;
	precedantTmp = M->precedant;
	suivantTmp->precedant = M;
	precedantTmp->suivant = N;
	M->suivant = suivantTmp;
	N->suivant = M;	
	N->precedant = precedantTmp;
	

	
}

Arbre* Arbre_Traitement(Arbre *H, Noeud *Q){
	vector<Noeud*> Gamma_Q; //Le chemin à la racine
	Noeud *P = Q;
	int echanger = 0;
	int indice;

	if(P == H->racine){
		Gamma_Q.push_back(P);
	}else{
		while(P != H->racine){
			Gamma_Q.push_back(P);
			P = Noeud_get_pere(P);
		}
		Gamma_Q.push_back(P);
	}

	//Parcourir les valeurs de Gamma_Q, verifier P
	if(Gamma_Q.size()!=1){
		for(unsigned int i=0;i<Gamma_Q.size()-1;i++){
			if(Noeud_get_poids(Gamma_Q[i])>=Noeud_get_poids(Noeud_get_suivant(Gamma_Q[i]))){
				echanger = 1;
				indice = i;
				break;
			}
		}
	}
	
	if(echanger == 0){ //Si P satisfaite on incrémente les poids
		for(unsigned int i=0;i<Gamma_Q.size();i++){
			Gamma_Q[i]->poids++;
		}	
	}else{	//Sinon echanger apres avoir incrémenté les incrémentables
		Noeud *m = Gamma_Q[indice];
		Noeud *b = Arbre_finBloc(H,m);

		for(int i=0;i<indice;i++){
			Gamma_Q[i]->poids++;
		}
		m->poids++;
		Noeud_echanger(H,b,m);
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
			N,NULL,N_interne);


		Noeud_set_allPointers(N,NULL,NULL,
			N_interne,Arbre_get_feuilleSpeciale(H),N_interne);

		Noeud_set_allPointers(N_interne,Arbre_get_feuilleSpeciale(H),N,
			NULL,N,NULL);

		H->caracteres[H->nb_caracteres++] = c;
		H->racine = N_interne;
		H->racine->suivant = NULL;
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
			Noeud_get_filsDroit(Q),N,Q);

		Noeud_set_allPointers(N,NULL,NULL,
			Noeud_get_suivant(Arbre_get_feuilleSpeciale(H)),Arbre_get_feuilleSpeciale(H),N_interne);

		Noeud_set_allPointers(Arbre_get_feuilleSpeciale(H),NULL,NULL,
			N,NULL,N_interne);
		H->caracteres[H->nb_caracteres++] = c;
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

Noeud* Arbre_finBloc(const Arbre *H, Noeud *N){
	unsigned int poids = Noeud_get_poids(N);
	Noeud *P = N->suivant;
	Noeud *Q;
	if(Noeud_get_poids(P)>poids){
		return N;
	}
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

char * Arbre_code(const Arbre *H, Noeud *N){
	Noeud *tmp;
	tmp = N;
	char *code, buff[10];
	int i = 0;
	memset(buff,0,sizeof(buff));
	while (tmp!=H->racine){
		buff[i] = Noeud_code(tmp);
		tmp = Noeud_get_pere(tmp);
		i++;
	}
	buff[i+1]='\0';
	code = (char *)malloc(i*sizeof(char));
	//On inverse le code
	for(unsigned int j=0;j<strlen(buff);j++){
		code[j]=buff[strlen(buff)-j-1];
	}
	code[strlen(buff)]='\0';
	return code;
}

char * Arbre_code_FS(Arbre *H){
	char *retour;
	if(H->premiere_insertion){
		retour = (char*)malloc(2*sizeof(char));
		retour[0] = '0';
		retour[1] = '\0';
		return retour;
	}
	retour = Arbre_code(H,Arbre_get_feuilleSpeciale(H));
	return retour;
}

char * Arbre_code(Arbre *H, unsigned char c){
	char *retour = Arbre_code(H,Arbre_get_feuille(H,c));
	return retour;
}

void Noeud_affichage_recursif(const Noeud *N){
	if(N!=NULL){
		fprintf(stderr," { ");
		fprintf(stderr,"[%c - %d]", Noeud_get_char(N), Noeud_get_poids(N));
		Noeud_affichage_recursif(Noeud_get_filsGauche(N));
		Noeud_affichage_recursif(Noeud_get_filsDroit(N));
		fprintf(stderr," } ");
	}
	
}

void Arbre_affichage(const Arbre *H){
	Noeud_affichage_recursif(H->racine);
	fprintf(stderr, "\n");
}
