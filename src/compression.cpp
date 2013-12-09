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

void Decompression(int fd_entree, int fd_sortie){
	int i = 0, shift;
	char buff[100];
	Decode_buffer *dbf = Decode_buffer_init();
	Arbre *H = Arbre_creerVide();
	Noeud *N;

	if((total_char = read(fd_entree,buff,sizeof(buff))) < 0){
		perror("read du fichier d'entrée");
		exit(1);
	}
	//je commence par lire la feuille spéciale et le premier caractère
	char lettre = Code_getLettre(buff[0],buff[1],7);
	buff_sortie[0] = lettre;
	Arbre_Modification(H,lettre);

	N = H->racine;

	shift = 7;
	fprintf(stderr, "lettre = %c\n", lettre);
	i = 2;
	while(i < total_char - 1){ //Tant que j'ai des caractères à lire
		char c1 = buff[i]; // Je prends le caractère courant
		char c2 = buff[i+1];
		int bit = Code_Symbole_code_position(c1,shift);
		if (bit == 0)
			N = N->filsGauche;
		else
			N = N->filsDroit;
		if(Noeud_estFeuille(N)){
			
			if(N->caractere == '#')
				lettre = Code_getLettre(c1,c2,shift--);
			else
				lettre = N->caractere;
			buff_sortie[i] = lettre;
			Arbre_Modification(H,lettre);
			N = H->racine;
			i++;
		}	
		fprintf(stderr, "lettre = %c\n", lettre);
		
		
	}
	if(write(fd_sortie,buff_sortie,sizeof(buff_sortie))<0){
		perror("write du fichier de sortie");
		exit(2);
	}
	close(fd_entree);
	close(fd_sortie);
	Arbre_detruire(H);
}
