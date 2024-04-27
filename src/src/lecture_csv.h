#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#define MAX_CHAR_SIZE 512
#define MAX_VOTES_E 50

/**
 * @brief Cette fonction ouvre un fichier CSV et le stocke dans une matrice
 * @param nomFichier Nom du fichier à lire
 * @param matrice Matrice pour stocker les données du fichier
 */

void lireFichierCSV(char* nomFichier, t_mat_char_star_dyn* matrice);


// Fonction qui récupère les informations d'un fichier csv de vote pour remplire une structure de voteElecteur
void lireFichierCSV_vote(const char *nomFichier, voteElecteur **v_elect,nbElecteurs* nb_elect);

// Fonction qui récupère les informations d'un fichier csv de vote pour remplire une structure de Electeur
void lireFichierCSV_electeur(const char* nomFichier, electeur **electeurs,nbElecteurs* nb_elect);
#endif // LECTURE_CSV_H
