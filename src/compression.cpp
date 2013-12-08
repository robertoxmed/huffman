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
			Code_Symbole *s = Code_Symbole_init();
			char *code = Arbre_code(H,c);
			Code_Symbole_code(s,code,strlen(code));
			Code_buffer_transmettre(cbf,s);
			Code_Symbole_printBinaire(s);
			Code_Symbole_detruire(s);
		}else{
			Code_Symbole *s = Code_Symbole_init();
			Code_Symbole *s_fs = Code_Symbole_init();
			char *code = Arbre_code_FS(H);
			fprintf(stderr,"Code de la feuille: %s - %lu \n",code,strlen(code));
			Code_Symbole_code(s_fs,code,strlen(code));
			Code_Symbole_code_char(s,c);
			Code_buffer_transmettre(cbf,s_fs);
			Code_buffer_transmettre(cbf,s);
			fprintf(stderr,"Code_Symbole de la feuille speciale: " );
			Code_Symbole_printBinaire(s_fs);
			fprintf(stderr,"Code Symbole du caractere: ");
			Code_Symbole_printBinaire(s);
			Code_Symbole_detruire(s);
			Code_Symbole_detruire(s_fs);
		}
		Arbre_Modification(H,c);
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

void Decompression(int fd_entre, int fd_sortie){

}
