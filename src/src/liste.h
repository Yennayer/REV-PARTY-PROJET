/**
 * \file liste.h
 * \brief Header file defining operations and structures for handling a static list of 'Elementliste' type elements.
 *
 * Ce fichier définit des opérations et des structures pour gérer une liste statique d'éléments de type 'Elementliste'.
 * Il comprend des fonctions pour la création, l'ajout, la suppression, et d'autres opérations sur la liste.
 */

#ifndef LISTE_H
#define LISTE_H

#include "elementliste.h"
#include <stdbool.h>

#define DIMMAX 100
#define VIDE -1

struct liste {
    Elementliste Tabliste[DIMMAX];
    int Tete;
    int nbElt;
};

typedef struct liste liste;

int nbEltList(liste lst);
void createList(liste *p);
void addFrontList(liste *p, Elementliste e);
void addTailList(liste *p, Elementliste e);
void delTailList(liste *p);
void delFrontList(liste *p);
void headList(liste p, Elementliste *e);
void tailList(liste p, Elementliste *e);
bool emptyList(liste p);
bool fullList(liste p);
void dumpList(liste p, FILE *fp);
void swapEltList(Elementliste *a, Elementliste *b);
void bubbleSortList(liste *p);
void pickEltList(liste l, Elementliste *e, int index);
bool belongEltList(liste p, Elementliste e);

#endif // LISTE_H

