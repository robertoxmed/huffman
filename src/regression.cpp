/*
 * Algav: Projet Arbre Huffman Adaptative
 * regression.cpp: pour tester que les fonctions font bien ce qu'on souhaite
 *
 * Roberto MEDINA
 *
 * 10 Décembre 2013
 */

#include "../include/arbre.hpp"
#include "../include/codage.hpp"
#include "../include/compression.hpp"

int main (){

	Arbre *H;

	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=  Tests de regression Huffman Dynamique  =\n");
	fprintf(stderr, "===========================================\n\n");

	fprintf(stderr, "\n---------------------------------------------\n");
	fprintf(stderr, "-            Tests sur les arbres           -\n");
	fprintf(stderr, "----------------------------------------------\n\n");
	//Création d'un arbre vide et on l'affiche
	H=Arbre_creerVide();
	fprintf(stderr, "Arbre vide: %c %d\n", H->racine->caractere, H->racine->poids);
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'b');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'r');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'c');
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'d');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'b');
	Arbre_affichage(H);
	H = Arbre_Modification(H,'r');
	H = Arbre_Modification(H,'a');
	Arbre_affichage(H);

	fprintf(stderr, "\nLe code de a : %s\n", Arbre_code(H,'a'));
	fprintf(stderr, "Le code de b : %s\n", Arbre_code(H,'b'));
	fprintf(stderr, "Le code de d : %s\n", Arbre_code(H,'d'));
	
	fprintf(stderr, "\n---------------------------------------------\n");
	fprintf(stderr, "-            Tests sur les symboles         -\n");
	fprintf(stderr, "---------------------------------------------\n\n");

	fprintf(stderr, "Affichage des Symboles:\n\n");

	Code_Symbole *s_b = Code_Symbole_init();
	Code_Symbole *s_d = Code_Symbole_init();
	Code_Symbole_code_char(s_b,'b');
	fprintf(stderr, "Le code dans le buffer pour la lettre b : ");
	Code_Symbole_printBinaire(s_b);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s_b->code, s_b->taille);

	char * code = Arbre_code(H,'d');
	char * code_fs = Arbre_code_FS(H);
	Code_Symbole_code(s_d,code,strlen(code));
	fprintf(stderr, "Le code dans le buffer pour la lettre d en prennant en compte l'arbre: ");
	Code_Symbole_printBinaire(s_d);
	fprintf(stderr, "Dans le symbole: %c - %d\n", s_d->code, s_d->taille);


	fprintf(stderr, "Est-ce que j'ai un 1 à la position 8: %d\n", Code_Symbole_code_position(s_d->code,8));

	Code_Symbole *s_fs = Code_Symbole_init();
	Code_Symbole_code(s_fs, code_fs, strlen(code_fs));
	fprintf(stderr, "Le code de la feuille spéciale = %s\n", code_fs);
	Code_buffer *cbf = Code_buffer_init();

	fprintf(stderr, "\nAffichage du Code buffer:\n");
	
	
	Code_buffer_transmettre(cbf,s_fs);
	Code_buffer_transmettre(cbf,s_b);
	Code_buffer_transmettre(cbf,s_d);
	Code_buffer_printBinaire(cbf);

	int fd_entree = open("demo/test", O_RDONLY);
	int fd_sortie = open("demo/test.huffman", O_WRONLY|O_CREAT|O_TRUNC, 0600);

	fprintf(stderr, "\nOn va compresser le fichier \"test\" contenant abracadabra\n");

	Compression(fd_entree,fd_sortie);

	int fd2_entree = open("demo/test.huffman", O_RDONLY);
	int fd2_sortie = open("demo/test.decompress", O_WRONLY|O_CREAT|O_TRUNC, 0600);

	fprintf(stderr, "\nOn va decompresser le fichier \"test\" contenant abracadabra\n");

	Decompression(fd2_entree,fd2_sortie);

	fprintf(stderr, "\nOn libère les structures allouées.\n");
	close(fd_entree);
	close(fd_sortie);
	close(fd2_entree);
	close(fd2_sortie);
	Code_Symbole_detruire(s_b);
	Code_Symbole_detruire(s_d);
	Arbre_detruire(H);


	fprintf(stderr, "\n===========================================\n");
	fprintf(stderr, "=               Fin des tests             =\n");
	fprintf(stderr, "===========================================\n\n");

	return EXIT_SUCCESS;
}
