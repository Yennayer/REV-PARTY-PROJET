#ifndef REV_PARTY_UTILS_SD_H
#define REV_PARTY_UTILS_SD_H
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///  libération de la mémoire allouée à la matrice
/// \param[in] matrice_csv la matrice de type t_mat_char_star_dyn à libérer
void liberer_matrice_char(t_mat_char_star_dyn * matrice_csv);

///  libération de la mémoire allouée à la matrice
/// \param[in] matrice_duel la matrice de type t_mat_int_dyn à libérer
void liberer_matrice_int(t_mat_int_dyn * matrice_duel);


///  libération de la mémoire allouée à la matrice
/// \param[in] tableau le tableau à libérer
void liberer_tab_int(t_tab_int_dyn * tableau);

///  procédure d'affichage des résultats de la lecture du csv
/// \param[in] matrice_csv la matrice t_mat_char_star_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_csv(t_mat_char_star_dyn * matrice_csv, FILE *outfp);

///  procédure d'affichage des résultats de la construction de la matrice de duels
/// \param[in] matrice_duel la matrice t_mat_int_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_duel(t_mat_int_dyn * t_tab, FILE *outfp);

///  procédure d'affichage des résultats de la construction de la matrice des arcs
/// \param[in] matrice_arc la matrice t_mat_int_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_arc(t_mat_int_dyn * t_tab, FILE *outfp);

/// procédure d'affichage des infos pratiques sur le fichier csv
/// \param matrice_csv la matrice t_mat_char_star_dyn contenant les infos à afficher
/// \param type_csv le type de csv (duel 0 ou ballot 1)
/// \param outfp
void afficher_infos_csv(t_mat_char_star_dyn * matrice_csv, int * type_csv, FILE *outfp);
/**
 * @brief Affiche une matrice d'entiers représentant les duels.
 * @param matrice Structure contenant la matrice des duels.
 */
void afficherMatricee(t_mat_int_dyn *matrice,FILE * outfp);
/// procédure d'affichage des résultat
/// \param mode_scrutin chaine de caractère définissant le mode de scrutin
/// \param gagnant chaine de caractère définissant le nom de gagnant
/// \param nb_candidats entier definissant le nb de candidats
/// \param nb_votants entier  definissant le nb de votants
/// \param score flotant  definissant le score si uninominal
/// \param logfp le flux de sortie
void afficher_resultat(char * mode_scrutin, char * gagnant, int nb_candidats, int nb_votants, float score, FILE * logfp);
void afficher_vainqueur(char nom_methode[], int nb_c, int nb_v, char nom_vainqueur[], int uni, int score, FILE * file);
#endif //REV_PARTY_UTILS_SD_H
