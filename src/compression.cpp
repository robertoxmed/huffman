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
	//fprintf(stderr, "total char = %d , buffer = %s\n", total_char, buff);

	while(i < total_char){ //Tant que j'ai des caractères à lire
		//fprintf(stderr, "Caractère à compresser %c\n", buff[i]);

		char c = buff[i];
		if(Arbre_recherche_char(H,c)){ //Si le caractère lu est dans l'arbre
			Symbole *s = Symbole_init();
			char *code = Arbre_code(H,c);
			Symbole_code(s,code,strlen(code));
			Code_buffer_transmettre(cbf,s);
		}else{
			Symbole *s = Symbole_init();
			Symbole *s_fs = Symbole_init();
			char *code = Arbre_code_FS(H);
			Symbole_code(s,code,strlen(code));
			Symbole_code_char(s,c);
			Code_buffer_transmettre(cbf,s_fs);
			Code_buffer_transmettre(cbf,s);
		}
		Arbre_Modification(H,c);
		i++;
	}

	if(write(fd_sortie,cbf->code_buffer,cbf->nb_octets)<0){
		perror("write du fichier de sortie");
		exit(2);
	}

}
