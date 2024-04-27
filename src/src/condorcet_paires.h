#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "duel.h"
#include "graph.h"

#ifndef CONDORCET_PAIRES_H
#define CONDORCET_PAIRES_H
/**
 * \file condorcet_pair.h
 * \brief Programme de recherche du vainqueur de Condorcet, appliquant éventuellement le classement des paires si besoin
 * \author Isra GUESMI 
 * \date 5 Décembre 2023 
 */


/**
 *@fn bool rechercheCycle(t_arc_p *de, t_arc_p *vers, int taille_de, int taille_vers, t_arc_p arcCourant);
 *@brief Vérifie s'il existe un arc qui confirmerait la présence d'un cycle dans le 'graphe'
 *@param[in] t_arc_p * de -> tableau des arcs possedant le même sommet que le sommet de départ de l'arc courant
 *@param[in] t_arc_p * vers -> tableau des arcs possedant le même sommet que le sommet d'arrivé de l'arc courant
 *@param[in] int taille_de 
 *@param[in] int taille_vers
 *@param[in] t_arc_p arcCourant -> arc courant qui servira de vérification afin de limité un peu plus le nombre de calcul
 *@return true signifie qu'il y a bel et bien un cycle dans le 'graphe', false signifie qu'il n'y a pas de cycle dans le 'graphe'
*/
bool findCycle(t_arc_p *debutarc, t_arc_p *vers, int taille_debutarc, int taille_vers, t_arc_p arcCourant);

/**
 *@fn void eliminationCycle(t_arc_p *tarc, t_arc_p *tarc_reduit, int *compteur, int taille_tarc);
 *@brief élimination des arcs qui forment engendrent des cycles dans le tableau ('graphe')
 *@param[in] t_arc_p *tarc -> tableau contenant les arcs des résultant des duels vainqueurs classé par ordre décroissant
 *@param[in, out] t_arc_p *tarc_reduit -> tableau qui contiendra tous les arcs qui ne créent pas de cycle dans le 'graphe'
 *@param[in, out] int * compteur -> permettra de sauvegarder le nombre d'arcs qui seront contenu dans tarc_reduit  (sera donc utilisable dans la suite du programme) 
 *@param[in] int taille_tarc 
*/
void eliminationCycle(t_arc_p *tarc, t_arc_p *tarc_reduit, int *compteur, int taille_tarc);

/**
 *@fn int condorcet_paires(t_mat_int_dyn *matrice_duels, FILE* log);
 *@brief Fonction qui effectue le déroulement complet de la méthode de Condorcet pairs 
 *@param[in] t_mat_int_dyn *matrice_duels -> matrice résultante de l'exécution de Condorcet et qui contient les résultats (non-traités) des duels pairs à pairs de Condorcet
 *@param[in] FILE * log -> fichier qui contiendra les logs a la fin de l'exécution du programme et qui permettra a l'utilisateur de vérifier les calculs
 *@return l'indice de la colonne de la matrice des duels qui correspondra donc au vainqueur de Condorcet
*/
int condorcet_paires(t_mat_int_dyn *matrice_duels, FILE* log);

/**
 *@fn void prog(char*filename, FILE* log, int option);
 *@brief fonction qui fait office de main. Elle traite le fichier csv, le converti, fait des affichages et test la version Condorcet normale avant d'appeler condorcet_pair si nécessaire 
 *@param[in] char*filename -> correspond au fichier csv passé en paramètre lors de l'exécution du programme
 *@param[in] FILE * log -> correspond au fichier log qui permettra a l'utilisateur de suivre le déroulement de l'éxecution du programme 
 *@param[in] int option -> précise le type de fichier qui est passé en paramètre 1 si c'est une matrice de duels ou 2 si c'est un ballot de votes
*/
void prog(char*filename, FILE* log, int option);
#endif /* CONDORCET_PAIRES_H */
