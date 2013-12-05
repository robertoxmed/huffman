/*
 * Algav: Projet Arbre Huffman Adaptative
 * symbole.cpp: Pour l'implémentation de la manipulation des Symboles
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/symbole.hpp"

Symbole * Symbole_init(){
	Symbole * retour;
	retour = (Symbole *)malloc(sizeof(Symbole));
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

void Symbole_detruire (Symbole *s){
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

void Symbole_code_char(Symbole *s, char c){
	if(s!=NULL){
		s->code = c;
		s->taille = 8;
	}
}

void Symbole_code(Symbole *s, char *code, int taille){
	int cpt = taille-1;
	for(int i=0;i<taille;i++)
		s->code &= ~(1 << i);
	for(int i=taille;i<8;i++){
		if(code[cpt] == '1'){
			s->code |= (1 << i);
		}else{
			s->code &= ~(1 << i);
		}
			
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
		tmp = tmp >>1;
	}
}

void Symbole_printBinaire(const Symbole *s){
	printBinaire_char(s->code);
	fprintf(stderr, " - %d\n", s->taille);
}

int Symbole_code_position(const char c, const int position){
	int real_position = 8-position;
	if (c & (1<<real_position))
  		return 1;
	else
  		return 0;
}

void Code_buffer_transmettre(Code_buffer *cbf, Symbole *s){
	int cpt = s->taille;

	if(s->taille > cbf->nb_bits){ // Si je dépasse l'octet courrant
		int diff = s->taille - cbf->nb_bits;

		//Ecrire sur ce qui reste de l'octet
		for(int i=cbf->nb_bits;i>=0;i--){ //Boucle pour savoir où écrire le bit du caractère courant
			if(Symbole_code_position(s->code,cpt)) //Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (7-i));
			else
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (7-i));
			cpt--;
		}
		cbf->octet_courant++;
		cbf->nb_octets++;
		cbf->nb_bits = 8;

			//On écrit sur le nouveau octet
		for(int i=7;i>=diff;i--){
			if(Symbole_code_position(s->code,cpt)){//Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (7-i));
				cbf->nb_bits--;
			}else{
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (7-i));
				cbf->nb_bits--;
			}
			cpt--;
		}

	}else{ //Si je ne depasse pas l'octet courant
		int diff = cbf->nb_bits - s->taille;

		for(int i=cbf->nb_bits-1;i>=diff;i--){
			if(Symbole_code_position(s->code,cpt)){//Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (7-i));
			}else{

				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (7-i));
			}
			cpt--;	
		}

		if(diff == 0){ //Pile ce qui reste d'un octet
			cbf->octet_courant++;
			cbf->nb_octets++;
			cbf->nb_bits = 8;
		}else{ //Sinon 
			cbf->nb_bits -= diff+1;
		}
	}
}

void Code_buffer_printBinaire(const Code_buffer * cbf){
	for(int i=0;i<=cbf->nb_octets;i++){
		printBinaire_char(cbf->code_buffer[i]);
	}
	fprintf(stderr, " - nb octets %d - nb bits restants %d\n", cbf->nb_octets, cbf->nb_bits);
}
