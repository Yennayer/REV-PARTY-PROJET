/**
 * \file Condorcet.h
 * \brief Déclarations et documentations des méthodes Condorcet
 * \date 05/12/2023
 *
 * Ce fichier contient les déclarations des méthodes liées à la méthode Condorcet,
 * telles que la recherche du vainqueur Condorcet et le calcul du gagnant selon le
 * critère minimax.
 */

#ifndef CONDORCET_H
#define CONDORCET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "global.h"

#include "lecture_csv.h"
#include "matrice.h"
#include "graph.h"

/**
 * @brief Recherche du vainqueur Condorcet dans un graphe
 *
 * Cette fonction recherche le vainqueur Condorcet dans un graphe donné. 
 * Le vainqueur est le candidat qui n'a aucun prédécesseur dans le graphe.
 *
 * @param graphe Le graphe représentant les relations de duel entre les candidats.
 * @return Le nom du vainqueur Condorcet ou NULL s'il n'y en a pas.
 */
char *winnerCondorcet(graph *graphe);

/**
 * @brief Application du scrutin Condorcet à partir d'un fichier CSV.
 *
 * Cette fonction lit un fichier CSV, construit la matrice duel, renvoie le vainqueur condorcet
 *
 * @param f Le nom du fichier CSV contenant les résultats du scrutin.
 */
void condorcet(char *f);

/**
 * @brief Calcul du gagnant selon le critère minimax.
 *
 * Cette fonction calcule le gagnant d'un scrutin Condorcet en utilisant le critère minimax.
 * Le gagnant est le candidat ayant le score maximal minimal contre tous les autres candidats.
 *
 * @param mat_duel La matrice duel représentant les scores des duels entre les candidats.
 * @return L'indice du gagnant dans la matrice duel.
 */
int winnerMinimax(t_mat_int_dyn *mat_duel);

/**
 * @brief Application du scrutin Condorcet minimax à partir d'un fichier CSV.
 *
 * Cette fonction lit un fichier CSV, construit la matrice duel, applique le scrutin
 * Condorcet minimax, puis affiche le résultat.
 *
 * @param fileName Le nom du fichier CSV contenant les résultats du scrutin.
 */
void minimax(char *fileName);

/**
 * @brief Construit la structure de résultats en fonction de l'option spécifiée et du fichier d'entrée.
 * @param option Option de sélection de la méthode.
 * @param filename Nom du fichier d'entrée.
 * @return Pointeur vers la structure Resultats allouée dynamiquement.
 */
Resultats *construction_mat_duels(int option, char *filename,FILE*outfp);

int condorcet1(t_mat_int_dyn *matriceDuels, FILE *outfp);
#endif /* CONDORCET_H */
