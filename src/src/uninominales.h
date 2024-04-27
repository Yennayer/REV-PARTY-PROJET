#ifndef REV_PARTY_UNINOMINALES_H
#define REV_PARTY_UNINOMINALES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice.h"
#include "global.h"

// Déclaration de la fonction trouver_gagnant_un_tour
void calculerSommecolonnes(const t_mat_char_star_dyn* matrice, int sommeColonnes[]);
int trouverColonneMax(t_mat_char_star_dyn *mat) ;

void afficher_vainqueur(t_mat_char_star_dyn *mat);
void calculerDeuxPremiers(t_mat_char_star_dyn *mat, int *premier, int *second) ;
void afficher_vainqueurs_deux_tours(t_mat_char_star_dyn *mat);
void afficherResultatsDeuxTours(t_mat_char_star_dyn *mat) ;
#endif //REV_PARTY_UNINOMINALES_H