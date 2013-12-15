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
	char buff[5000];
	int total_char = 0;
	Code_buffer * cbf = Code_buffer_init();
	Arbre *H = Arbre_creerVide();

	if((total_char = read(fd_entree,buff,sizeof(buff))) < 0){
		perror("read du fichier d'entrée");
		exit(1);
	}
	while(i < total_char-1){ //Tant que j'ai des caractères à lire
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
	Arbre_affichage(H);
	Code_buffer_printBinaire(cbf);

	if(write(fd_sortie,cbf->code_buffer,cbf->nb_octets)<0){
		perror("write du fichier de sortie");
		exit(2);
	}
	close(fd_entree);
	close(fd_sortie);
	Arbre_detruire(H);
	Code_buffer_detruire(cbf);

}

void Decompression(int fd_entree, int fd_sortie){
	int i = 0;
	int total_char;
	char buff[5000], lettre;
	Decode_buffer *dbf = Decode_buffer_init();
	Arbre *H = Arbre_creerVide();
	Noeud *N;

	//je charge le code compressé dans la structure de décodage
	if((total_char = read(fd_entree,dbf->decode_buffer,sizeof(dbf->decode_buffer))) < 0){
		perror("read du fichier d'entrée");
		exit(1);
	}

	//je commence par lire la feuille spéciale et le premier caractère
	Decode_Next(dbf);
	lettre = Decode_getLettre(dbf);
	buff[i] = lettre;
	Arbre_Modification(H,lettre);

	fprintf(stderr, "lettre = %c ", buff[i]);
	i++;
	N = H->racine;
	while(dbf->octet_courant < total_char+1){ //Tant que j'ai des caractères à lire

		while(!Noeud_estFeuille(N)){
			int bit = Decode_get_Next(dbf);
			if (bit == 0)
				N = N->filsGauche;
			else
				N = N->filsDroit;
		}
		
		if(N->caractere == '#') //Si je lis la feuille spéciale
			lettre = Decode_getLettre(dbf); //Je recupère la lettre	
		else
			lettre = N->caractere;

		buff[i] = lettre;
		Arbre_Modification(H,buff[i++]);
		N = H->racine;
		fprintf(stderr, "lettre = %c ", buff[i-1]);

	}
	fprintf(stderr, "\n");
	Arbre_affichage(H);

	if(write(fd_sortie,buff,i-1)<0){
		perror("write du fichier de sortie");
		exit(2);
	}
	close(fd_entree);
	close(fd_sortie);
	Arbre_detruire(H);
	Decode_buffer_detruire(dbf);

}

