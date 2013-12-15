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

Decode_buffer * Decode_buffer_init(){
	Decode_buffer * retour;
	retour = (Decode_buffer*)malloc(sizeof(Decode_buffer));
	retour->position_bit = 8;
	retour->octet_courant = 0;
	return retour;
}

void Code_Symbole_detruire (Code_Symbole *s){
	if(s!=NULL)
		free(s);
}

void Code_buffer_detruire (Code_buffer *cbf){
	if( cbf != NULL ){
		free(cbf);
	}
}

void Decode_buffer_detruire (Decode_buffer *dbf){
	if( dbf != NULL ){
		free(dbf);
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
	int position = 8;
	if(s->taille > cbf->nb_bits){ // Si je dépasse l'octet courrant
		int diff = s->taille - cbf->nb_bits;
		//Ecrire sur ce qui reste de l'octet
		for(int i=cbf->nb_bits;i>0;i--){ //Boucle pour savoir où écrire le bit du caractère courant
			if(Code_Symbole_code_position(s->code,position)) //Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (8-i));
			else
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (8-i));
			position--;
		}
		cbf->octet_courant++;
		cbf->nb_octets++;
		cbf->nb_bits = 8;
		//On écrit sur le nouveau octet
		for(int i=8;i>8-diff;i--){
			if(Code_Symbole_code_position(s->code,position))//Si le bit de la position cpt est à 1
				cbf->code_buffer[cbf->octet_courant] |= (1 << (8-i));
			else
				cbf->code_buffer[cbf->octet_courant] &= ~(1 << (8-i));
			cbf->nb_bits--;
			position--;
		}

	}else{ //Si je ne depasse pas l'octet courant
		int diff = cbf->nb_bits - s->taille;
	
		for(int i=cbf->nb_bits;i>diff;i--){
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
			cbf->nb_bits -= s->taille;
		}
	}
}

void Code_buffer_printBinaire(const Code_buffer * cbf){
	for(int i=0;i<=cbf->nb_octets;i++){
		printBinaire_char(cbf->code_buffer[i]);
	}
	fprintf(stderr, " - nb octets %d - nb bits restants %d\n", cbf->nb_octets, cbf->nb_bits);
}

void Decode_Next(Decode_buffer *dbf){
	if(dbf->position_bit == 1){
		dbf->position_bit = 8;
		dbf->octet_courant++;
	}else
		dbf->position_bit--;
}

int Decode_get_Next(Decode_buffer *dbf){
	if(Code_Symbole_code_position(dbf->decode_buffer[dbf->octet_courant],dbf->position_bit)){
		Decode_Next(dbf);
		return 1;
	}
	Decode_Next(dbf);
	return 0;
}

char Decode_getLettre(Decode_buffer *dbf){
	if(dbf->position_bit == 8) //Je renvoie tout l'octet
		return dbf->decode_buffer[dbf->octet_courant++];
	else{
		char retour = 0;
		int position = dbf->position_bit;
		for(int i=8;i>8-dbf->position_bit;i--){ //J'ecris sur les 8 - shift premiers bits
			if(Code_Symbole_code_position(dbf->decode_buffer[dbf->octet_courant],position))
				retour |= (1 << (8-i));
			else
				retour &= ~(1 << (8-i));
			position--;
		}
		position = 8;
		for(int i=8-dbf->position_bit;i>0;i--){
			if(Code_Symbole_code_position(dbf->decode_buffer[dbf->octet_courant+1],position))
				retour |= (1 << (8-i));
			else
				retour &= ~(1 << (8-i));
			position--;
		}
		dbf->octet_courant++;
		return retour;
	}

}
