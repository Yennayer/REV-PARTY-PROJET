/*-----------------------------------------------------------------*/
/**
 * @file duel.h
 * @date 22/11/2023
 * @brief Structure Duel header
 * 
/*-----------------------------------------------------------------*/
#ifndef __DUEL_H__
#define __DUEL_H__
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

/**
 * @def DEFAULT_VALUE
 * @brief valeur par défaut d'une case
 * @note ne doit pas faire partie de l'ensemble des valeurs possibles des éléments stockés
*/
#define DEFAULT_VALUE -2


/**

 * @date 22/11/2023
 * @brief Définition opaque de la structure Duel
*/
typedef struct s_duel Duel;
typedef Duel * ptrDuel;


/**

 * @date 22/11/2023
 * @brief Crée une matrice de duels
 * 
 * @param[in] nbl Nombre de lignes de données (hors étiquettes)
 * @param[in] nbc Nombre de colonnes de données (hors étiquettes)
 * 
 * @return pointeur vers la matrice de duels, NULL si erreur
*/
Duel* createDuel(unsigned int nbl, unsigned int nbc);


/** 

 * @date 22/11/2023
 * @brief Supprime la matrice de duels et ses données en libérant la mémoire 
 * 
 * @param[in] d pointeur vers la matrice de duels à supprimer
*/
void deleteDuel(ptrDuel* d);


/**

 * @date 22/11/2023
 * @brief Ajoute un élément dans la matrice de duels à la position (l,c), l'élément
 * ne pourra plus être modifié
 * 
 * @param[in] d Matrice de duels à remplir
 * @param[in] l Ligne de destination
 * @param[in] c Colonne de destination
 * @param[in] v valeur à ajouter
 * @pre l < nb_ligne && c < nb_colonnes                                /!\ UTF-8 chars?
 * 
 * @return Adresse de la matrice de duels, NULL si erreur
*/
Duel* duelSetValue(Duel *d, unsigned int l, unsigned int c, int v);



/**

 * @date 22/11/2023
 * @brief Renvoie la valeur à la position (l,c) dans la matrice de duel
 * 
 * @param[in] d matrice de duels à lire
 * @param[in] l Ligne de la valeur
 * @param[in] c Colonne de la valeur
 * @pre l < nb_ligne && c < nb_colonnes
 * 
 * @return la valeur en position (l, c), -1 si erreur 
 */
int duelGet(Duel* d, unsigned int l, unsigned int c);


/**

 * @date 22/11/2023
 * @brief Renvoie les dimension de la matrice de duels sous la forme d'un couple (nb_lignes, nb_colonnes)
 * 
 * @param[in] d matrice de duels à utiliser
 * 
 * @return tableau d'entier de taille 2 : [nombre_lignes, nombre_colonnes], NULL si erreur
 */
unsigned int* duelShape(Duel* d);


/**

 * @date 22/11/2023
 * @brief Met une étiquette à la colonne et à la ligne d'indice ind
 * @note Par défaut l'étiquette vaut NULL
 * 
 * @param[in] d matrice de duels à modifier
 * @param[in] ind Indice de la colonne / ligne
 * @param[in] label Etiquette
 * @pre c < nb_colonnes
 * 
 * @return -1 si erreur, 0 sinon
 */
int duelSetLabel(Duel* d, unsigned int ind, char* label);

/**
=
 * @date 22/11/2023
 * @brief Renvoie le numéro de la colonne associée à l'étiquette
 * 
 * @param[in] d matrice de duels à utiliser
 * @param[in] label  Etiquette de la colonne recherchée
 * 
 * @return numéro de la colonne, -1 si erreur 
 */
int duelGetColumn(Duel* d, char* label);



/**

 * @date 22/11/2023
 * @brief Renvoie le numéro de la ligne associée à l'étiquette
 * 
 * @param[in] d matrice de duels à utiliser
 * @param[in] label  Etiquette de la ligne recherchée
 * 
 * @return numéro de la ligne,-1 si erreur 
 */
int duelGetLine(Duel* d, char* label);


/**
 * @date 22/11/2023
 * @brief Renvoie la valeur associée au duel label1 vs label2
 * 
 * @param[in] d matrice de duels à lire
 * @param[in] label1 nom du premier candidat
 * @param[in] label2 nom du deuxème candidat
 * @pre label1 et label2 sont des candidats valides
 * 
 * @return la valeur en position (l, c), -1 si erreur 
 */
int duelGetVS(Duel* d, char* label1, char* label2);








#ifdef DEBUG

void printDuelLog(Duel* d);

#endif

#endif
