/**
 * Algav: Projet Arbre Huffman Adaptative
 * compression.hpp: entêtes pour la compression et la décompression d'un texte
 *
 * Roberto MEDINA
 * 
 * 10 Décembre 2013
*/

#ifndef __COMPRESSION__
#define __COMPRESSION__

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "arbre.hpp"
#include "codage.hpp"

/*---------------------------------------------
 	Definition des  entetes des fonctions
	pour la compression et la decompression
-----------------------------------------------*/

//Prend le texte T et le compresse pour compresser
void Compression(int fd_entree, int fd_sortie);

//Prend le texte 
void Decompression(int fd_entree, int fd_sortie);

#endif
