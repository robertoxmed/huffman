/**
 * Algav: Projet Arbre Huffman Adaptative
 * arbre.cpp: définit les fonctions de gestion de l'arbre
 *
 * Roberto MEDINA
 * 
 * 10 Décembre 2013
*/

#include "../include/compression.hpp"


void Compression(int fd_entree, int fd_sortie){
	int i = 0;
	char buff[100];
	int total_char = 0;
	Code_buffer * cbf = Code_buffer_init();
	Arbre *H = Arbre_creerVide();

	if((total_char = read(fd_entree,buff,sizeof(buff))) < 0){
		perror("read du fichier d'entrée");
		exit(1);
	}
	while(i < total_char){ //Tant que j'ai des caractères à lire

		char c = buff[i];
		if(Arbre_recherche_char(H,c)){ //Si le caractère lu est dans l'arbre
			Code_Symbole *s = Code_Symbole_init();
			char *code = Arbre_code(H,c);
			Code_Symbole_code(s,code,strlen(code));
			
			Code_buffer_transmettre(cbf,s);
			
			Code_Symbole_detruire(s);
		}else{
			Code_Symbole *s = Code_Symbole_init();
			Code_Symbole *s_fs = Code_Symbole_init();
			char *code = Arbre_code_FS(H);
			Code_Symbole_code(s_fs,code,strlen(code));
			Code_Symbole_code_char(s,c);
			
			Code_buffer_transmettre(cbf,s_fs);
			Code_buffer_transmettre(cbf,s);

			Code_Symbole_detruire(s);
			Code_Symbole_detruire(s_fs);
		}
		H = Arbre_Modification(H,c);
		i++;
	}

	Code_buffer_printBinaire(cbf);

	if(write(fd_sortie,cbf->code_buffer,cbf->nb_octets)<0){
		perror("write du fichier de sortie");
		exit(2);
	}
	close(fd_entree);
	close(fd_sortie);
	Arbre_detruire(H);
}

int Maj_position (const int position, const int op){
	int retour;
	if(op>position)
		retour = (8 - (op - position))%9;
	else
		retour = (position - op)%9;
	fprintf(stderr, "Retour = %d\n", retour);
	return retour;
}

void Decompression(int fd_entree, int fd_sortie){
	int i = 0, position, taille_code = 0;
	int total_char;
	char buff[100], lettre;
	Decode_buffer *dbf = Decode_buffer_init();
	Arbre *H = Arbre_creerVide();
	Noeud *N;

	if((total_char = read(fd_entree,buff,sizeof(buff))) < 0){
		perror("read du fichier d'entrée");
		exit(1);
	}
	//je commence par lire la feuille spéciale et le premier caractère
	Decode_getLettre(dbf,buff[0],buff[1],7);
	Arbre_Modification(H,dbf->decode_buffer[i]);
	N = H->racine;

	position = 7;
	int position2 = position;
	fprintf(stderr, "lettre = %c ", dbf->decode_buffer[i]);
	i++;
	while(i < total_char){ //Tant que j'ai des caractères à lire
		char c1 = buff[i]; // Je prends le caractère courant
		char c2 = buff[i+1]; //Et le suivant quand je dois lire un code sur deux octets soujacents
		while(!Noeud_estFeuille(N)){
			int bit = Code_Symbole_code_position(c1,position2--);
			if (bit == 0)
				N = N->filsGauche;
			else
				N = N->filsDroit;
			taille_code++;
		}
		
		if(N->caractere == '#'){
			position = Maj_position(position,taille_code);
			Decode_getLettre(dbf,c1,c2,position);
			i++;
		}else{
			lettre = N->caractere;
			Decode_putLettre(dbf,lettre);
			if(taille_code >= position) i++;
			position = Maj_position(position, taille_code);
		}
		Arbre_Modification(H,dbf->decode_buffer[dbf->octet_courant-1]);
		N = H->racine;
		taille_code = 0;
		position2 = position;
		fprintf(stderr, "lettre = %c ", dbf->decode_buffer[dbf->octet_courant-1]);

	}
	fprintf(stderr, "\n");
	Arbre_affichage(H);

	if(write(fd_sortie,dbf->decode_buffer,sizeof(dbf->octet_courant-1))<0){
		perror("write du fichier de sortie");
		exit(2);
	}
	close(fd_entree);
	close(fd_sortie);
	Arbre_detruire(H);
}
