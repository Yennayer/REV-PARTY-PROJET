/// \file liste.c
/// \brief Fichier source implémentant les fonctions de manipulation d'une liste statique.
/// \date 12/11/2023

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "elementliste.h"
#include "liste.h"

/**
 * \brief Initialise une liste.
 * \param p Pointeur vers la liste à initialiser.
 *
 * Cette fonction initialise une liste en mettant la tête de liste à 0 et le nombre d'éléments à 0.
 * Elle prépare la liste à être utilisée pour d'autres opérations.
 */
void createList(liste *p){
    p->Tete = 0; // Définit l'indice de la tête de liste.
    p->nbElt = 0; // Initialise le nombre d'éléments dans la liste à zéro.
}

/**
 * \brief Renvoie le nombre d'éléments dans une liste.
 * \param lst La liste dont on veut connaître le nombre d'éléments.
 * \return Le nombre d'éléments dans la liste.
 */
int nbEltList(liste lst){
    return lst.nbElt; // Renvoie le champ 'nbElt' de la liste.
}

/**
 * \brief Ajoute un élément au début de la liste.
 * \param p Pointeur vers la liste.
 * \param e Élément à ajouter.
 *
 * Cette fonction ajoute un élément au début de la liste. Si la liste est pleine, elle affiche
 * une erreur et quitte le programme.
 */
void addFrontList(liste *p, Elementliste e){
    if (fullList(*p)) { // Vérifie si la liste est pleine.
        fprintf(stderr, "addFront : liste pleine !\n");
        exit(1); // Quitte le programme si la liste est pleine.
    }
    // Calcule la nouvelle position de la tête de liste en tenant compte de la circularité.
    p->Tete = (p->Tete - 1 + DIMMAX) % DIMMAX;
    copie_element(&(p->Tabliste[p->Tete]), e); // Copie l'élément à la nouvelle tête.
    p->nbElt++; // Incrémente le nombre d'éléments.
}

/**
 * \brief Ajoute un élément à la fin de la liste.
 * \param p Pointeur vers la liste.
 * \param e Élément à ajouter.
 *
 * Cette fonction ajoute un élément à la fin de la liste. Si la liste est pleine, elle affiche
 * une erreur et quitte le programme.
 */
void addTailList(liste *p, Elementliste e){
    if (fullList(*p)) { // Vérifie si la liste est pleine.
        fprintf(stderr, "addTailList : liste pleine !\n");
        exit(1); // Quitte le programme si la liste est pleine.
    }
    copie_element(&(p->Tabliste[(p->Tete + p->nbElt) % DIMMAX]), e); // Copie l'élément à la fin de la liste.
    p->nbElt++; // Incrémente le nombre d'éléments.
}

/**
 * \brief Supprime l'élément de fin de la liste.
 * \param p Pointeur vers la liste.
 *
 * Cette fonction supprime l'élément de fin de la liste. Si la liste est vide, elle affiche
 * une erreur et quitte le programme.
 */
void delTailList(liste *p){
    if (emptyList(*p)) { // Vérifie si la liste est vide.
        fprintf(stderr, "delTail : liste vide !\n");
        exit(1); // Quitte le programme si la liste est vide.
    }
    // Ajuste la tête de liste et décrémente le nombre d'éléments.
    p->Tete = (p->Tete + 1) % DIMMAX;
    p->nbElt--;
}
/**
 * \brief Supprime l'élément en tête de la liste.
 * \param p Pointeur vers la liste.
 *
 * Supprime l'élément de tête de la liste en décrémentant le nombre d'éléments.
 * Si la liste est vide, affiche une erreur et quitte le programme.
 */
void delFrontList(liste *p){
    if (emptyList(*p)) {
        fprintf(stderr, "depiler : liste vide !\n");
        exit(1);
    } else {
        p->nbElt--;
    }
}
/**
 * \brief Récupère l'élément de tête de la liste sans le supprimer.
 * \param p Liste à partir de laquelle récupérer l'élément.
 * \param e Pointeur vers l'élément récupéré.
 *
 * Si la liste est vide, affiche une erreur et quitte le programme.
 */
void headList(liste p, Elementliste *e){
    if (!emptyList(p))
        *e = p.Tabliste[p.Tete];
    else {
        fprintf(stderr, "sommet : liste vide !\n");
        exit(1);
    }
}

/**
 * \brief Récupère l'élément de fin de la liste sans le supprimer.
 * \param p Liste à partir de laquelle récupérer l'élément.
 * \param e Pointeur vers l'élément récupéré.
 *
 * Si la liste est vide, affiche une erreur et quitte le programme.
 */
void tailList(liste p, Elementliste *e){
    if (!emptyList(p))
        *e = p.Tabliste[(p.Tete + p.nbElt) % DIMMAX];
    else {
        fprintf(stderr, "sommet : liste vide !\n");
        exit(1);
    }
}
/**
 * \brief Vérifie si la liste est vide.
 * \param p Liste à vérifier.
 * \return true si la liste est vide, false sinon.
 */
bool emptyList(liste p) {
    return (p.nbElt == 0);
}

/**
 * \brief Vérifie si la liste est pleine.
 * \param p Liste à vérifier.
 * \return true si la liste est pleine, false sinon.
 */
bool fullList(liste p) {
    return (p.nbElt == DIMMAX);
}

/**
 * \brief Affiche le contenu de la liste.
 * \param p Liste à afficher.
 * \param fp Pointeur vers un fichier où afficher le contenu de la liste.
 *
 * Affiche chaque élément de la liste dans le fichier spécifié.
 */
void dumpList(liste p,FILE *fp){
  fprintf(fp,"\n(orig, dest, pds)\n");
	for(int ind=p.Tete;ind<p.Tete+p.nbElt%DIMMAX;ind++){
    fprintf(fp,"elt %d=",ind%DIMMAX);
    afficher_element(p.Tabliste[ind%DIMMAX],fp);
    }
}

void swapEltList(Elementliste *a,Elementliste *b)

{
    Elementliste aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void bubbleSortList(liste *p){

	int i,j;
	for (i=p->Tete;i<p->Tete+p->nbElt%DIMMAX;i++)
		for(j=i+1;j<p->Tete+p->nbElt%DIMMAX;j++)
			if ((p->Tabliste[i]).poids<(p->Tabliste[j]).poids)
			swapEltList(&(p->Tabliste[i]),&(p->Tabliste[j]));
}

void pickEltList(liste l,Elementliste *e,int index){
  
    int nbElt = l.nbElt;
    int indice = l.Tete+index%DIMMAX;
    if (index<0 || index >nbElt){
        printf("erreur d'indice dans la liste\n");
        return;
    }
    *e = l.Tabliste[indice];
}

bool belongEltList(liste p,Elementliste e){
  
    for(int ind=p.Tete;ind<p.Tete+p.nbElt%DIMMAX;ind++){
        if (cmp_elements(p.Tabliste[ind],e))
            return true;
    }
    return false;
}
