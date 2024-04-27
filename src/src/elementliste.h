/**
 * \file elementliste.h
 * \brief Header file defining operations and types for list elements, specifically for 't_arc_p' type elements.
 *
 * Ce fichier définit des opérations et des types pour les éléments de liste, plus particulièrement pour les éléments de type 't_arc_p'.
 * Il fournit des fonctions pour la saisie, la copie, l'affichage et la comparaison des éléments de ce type.
 */

#ifndef ELEMENTLISTE_H
#define ELEMENTLISTE_H

#include "global.h" // Inclut la définition du type t_arc_p

/**
 * \typedef Elementliste
 * \brief Type alias for 't_arc_p'.
 *
 * Alias de type pour 't_arc_p', utilisé pour représenter les éléments dans les listes.
 */
typedef t_arc_p Elementliste;

/**
 * \brief Saisit un élément de type 'Elementliste'.
 * \param e Pointeur vers l'élément de type 'Elementliste' à remplir.
 *
 * Cette fonction permet de saisir les données pour un élément de type 'Elementliste'.
 * Elle pourrait interagir avec l'utilisateur pour remplir les champs de l'élément.
 */
void saisie_element(Elementliste *e);

/**
 * \brief Copie un élément 'Elementliste' dans un autre.
 * \param cible Pointeur vers l'élément de type 'Elementliste' destinataire de la copie.
 * \param source Élément de type 'Elementliste' à copier.
 *
 * Cette fonction copie les données de l'élément 'source' dans l'élément pointé par 'cible'.
 */
void copie_element(Elementliste *cible, Elementliste source);

/**
 * \brief Affiche un élément de type 'Elementliste'.
 * \param e Élément de type 'Elementliste' à afficher.
 * \param fp Pointeur vers un fichier (FILE) où l'élément sera affiché.
 *
 * Cette fonction affiche les données de l'élément 'e' dans le fichier pointé par 'fp'.
 * L'affichage peut être formaté pour la lisibilité.
 */
void afficher_element(Elementliste e, FILE *fp);

/**
 * \brief Compare deux éléments de type 'Elementliste'.
 * \param e1 Premier élément de type 'Elementliste' pour la comparaison.
 * \param e2 Second élément de type 'Elementliste' pour la comparaison.
 * \return Renvoie 'true' si les éléments sont égaux, sinon 'false'.
 *
 * Cette fonction compare deux éléments 'e1' et 'e2' et renvoie 'true' s'ils sont considérés comme équivalents,
 * sinon 'false'. La définition de "équivalent" dépend de la structure de 'Elementliste'.
 */
bool cmp_elements(Elementliste e1, Elementliste e2);

#endif // ELEMENTLISTE_H

