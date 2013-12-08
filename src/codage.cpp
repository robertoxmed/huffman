/*
 * Algav: Projet Arbre Huffman Adaptative
 * symbole.cpp: Pour l'implémentation de la manipulation des Symboles
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/codage.hpp"

Code_Symbole * Code_Symbole_init(){
	Code_Symbole * retour;
	retour = (Code_Symbole *)malloc(sizeof(Code_Symbole));
	retour->code=0;
	retour->taille=0;
	return retour;
}

Code_buffer * Code_buffer_init(){
	Code_buffer * retour;
	retour = (Code_buffer*)malloc(sizeof(Code_buffer));
	retour->nb_bits = 8;
	retour->octet_courant = 0;
	retour->nb_octets = 0;
	return retour;
}

void Code_Symbole_detruire (Code_Symbole *s){
	if(s!=NULL)
		free(s);
}

void Code_buffer_detruire (Code_buffer *cbf){
	if( cbf != NULL ){
		for(int i=0;i<cbf->nb_octets;i++){
			free(&cbf->code_buffer[i]);
		}
		free(cbf);
	}
}

void Code_Symbole_code_char(Code_Symbole *s, char c){
	if(s!=NULL){
		s->code = c;
		s->taille = 8;
	}
}

void Code_Symbole_code(Code_Symbole *s, char *code, int taille){
	int cpt = taille-1;
	
	for(int i=0;i<8-taille;i++)
		s->code &= ~(1 << (7-i));
	for(int i=8-taille;i<8;i++){
		if(code[cpt] == '1')
			s->code |= (1 << (7-i));
		else
			s->code &= ~(1 << (7-i));
		cpt--;
	}
	s->taille = taille;
}

void printBinaire_char(const char c){
	char tmp = c;
	for(int i=0;i<8;i++){
		if(tmp & 1)
			fprintf(stderr, "1 ");
		else
			fprintf(stderr, "0 ");
		tmp >>= 1;
	}
}

void Code_Symbole_printBinaire(const Code_Symbole *s){
	printBinaire_char(s->code);
	fprintf(stderr, " - %d\n", s->taille);
}

int Code_Symbole_code_position(const char c, const int position){
	int real_position = (8 - position);
	if(c & (1 << real_position))
		return 1;
	return 0;
}

void Code_buffer_transmettre(Code_buffer *cbf, Code_Symbole *s){
	int cpt = 8;

	if(s->taille > cbf->nb_bits){ // Si je dépasse l'octet courrant
		int diff = s->taille - cbf->nb_bits;

		//Ecrire sur ce qui reste de l'octet
		for(int i=cbf->nb_bits;i>=0;i--){ //Boucle pour savoir où écrire le bit du caractère courant
			if(Code_Symbole_code_position(s->code,cpt)) //Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (7-i));
			else
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (7-i));
			cpt--;
		}
		cbf->octet_courant++;
		cbf->nb_octets++;
		cbf->nb_bits = 8;

			//On écrit sur le nouveau octet
		for(int i=8;i>=8-diff;i--){
			if(Code_Symbole_code_position(s->code,cpt))//Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (8-i));
			else
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (8-i));
			cbf->nb_bits--;
			cpt--;
		}

	}else{ //Si je ne depasse pas l'octet courant
		int position = 8;
		int diff = cbf->nb_bits - s->taille;
	
		for(int i=cbf->nb_bits;i>=diff;i--){
			if(Code_Symbole_code_position(s->code,position)){//Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (8-i));
			}else{

				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (8-i));
			}
			position --;	
		}

		if(diff == 0){ //Pile ce qui reste d'un octet
			cbf->octet_courant++;
			cbf->nb_octets++;
			cbf->nb_bits = 8;
		}else{ //Sinon 
			cbf->nb_bits -= s->taille+1;
		}
	}
}

void Code_buffer_printBinaire(const Code_buffer * cbf){
	for(int i=0;i<=cbf->nb_octets;i++){
		printBinaire_char(cbf->code_buffer[i]);
	}
	fprintf(stderr, " - nb octets %d - nb bits restants %d\n", cbf->nb_octets, cbf->nb_bits);
}