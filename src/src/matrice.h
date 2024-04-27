/**
 * @file matrice.h
 * @brief Fichier d'en-tête contenant les opérations et structures de matrice.
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "matrice.h"
#include "global.h"


/**
 * @brief Crée une matrice dynamique vide pour les caractères.
 * @return Un pointeur vers la matrice créée.
 */
t_mat_char_star_dyn *creer_matrice_char();

/**
 * @brief Libère la mémoire d'une matrice dynamique de caractères.
 * @param matrice La matrice à libérer.
 */
void supprimer_matrice_char(t_mat_char_star_dyn *matrice);

/**
 * @brief Retourne le nombre de colonnes dans la matrice de caractères.
 * @param matrice La matrice en entrée.
 * @return Le nombre de colonnes.
 */
int get_nb_colonnes(t_mat_char_star_dyn *matrice);

/**
 * @brief Retourne le nombre de lignes dans la matrice de caractères.
 * @param matrice La matrice en entrée.
 * @return Le nombre de lignes.
 */
int get_nb_lignes(t_mat_char_star_dyn *matrice);

/**
 * @brief Vérifie si la matrice de caractères est vide.
 * @param matrice La matrice en entrée.
 * @return 1 si la matrice est vide, 0 sinon.
 */
int est_matrice_vide(t_mat_char_star_dyn *matrice);

/**
 * @brief Récupère les noms des candidats à partir de la matrice de caractères.
 * @param matrice La matrice en entrée.
 * @return Un tableau de noms de candidats.
 */
char **get_candidats(t_mat_char_star_dyn *matrice);

/**
 * @brief Affiche la matrice de caractères.
 * @param matrice La matrice en entrée.
 */
void print_matrice_char(const t_mat_char_star_dyn *matrice);

/************************************************************************************************************************************/


/**
 * @brief Construit une matrice duelle à partir d'une matrice de caractères.
 * @param matrice La matrice de caractères en entrée.
 * @return Un pointeur vers la matrice duelle construite.
 */
t_mat_int_dyn *construire_mat_duel(t_mat_char_star_dyn *matrice);

/**
 * @brief Convertit une matrice de caractères en une matrice duelle.
 * @param matrice La matrice de caractères en entrée.
 * @return Un pointeur vers la matrice duelle convertie.
 */
t_mat_int_dyn *mat_char_to_mat_duel(t_mat_char_star_dyn *matrice);

/**
 * @brief Calcule le score maximal d'un candidat dans une matrice duel.
 *
 * La fonction parcourt la colonne spécifiée pour trouver le score maximal
 * d'un candidat, en ignorant la ligne correspondante au candidat lui-même.
 *
 * @param mat_duel La matrice duel.
 * @param iCandidat L'indice du candidat pour lequel calculer le score maximal.
 * @return Le score maximal du candidat.
 */
int scoreMaxCandidat(t_mat_int_dyn *mat_duel, int iCandidat);


/**
 * @brief Affiche la matrice duelle.
 * @param mat_duel La matrice duelle en entrée.
 */
void print_matrice_int(t_mat_int_dyn *mat_duel);

/**
 * @brief Libère la mémoire d'une matrice dynamique d'entiers.
 * @param mat_duel La matrice à libérer.
 */
void supprimer_matrice_int(t_mat_int_dyn *mat_duel);
void initialiserMatrice(MatriceDynamique *matriceDyn, int nbCandidats, int nbDuels);
void libererMatrice(MatriceDynamique *matriceDyn);

#endif /* MATRICE_H */
