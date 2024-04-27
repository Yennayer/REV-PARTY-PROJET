#include <stdio.h>
#include <stdbool.h>
#include "global.h"
#include "elementliste.h"

/**
 * \brief Copie un élément de type 'Elementliste' dans un autre.
 * \param cible Pointeur vers l'élément de type 'Elementliste' cible.
 * \param source Élément de type 'Elementliste' source à copier.
 *
 * Cette fonction effectue une copie superficielle de l'élément 'source' dans l'élément pointé par 'cible'.
 * Elle copie chaque champ individuellement de 'source' à 'cible'.
 */
void copie_element(Elementliste *cible, Elementliste source){
    cible->orig = source.orig;   // Copie le noeud d'origine
    cible->dest = source.dest;   // Copie le noeud de destination
    cible->poids = source.poids; // Copie le poids de l'arc
}

/**
 * \brief Compare deux éléments de type 'Elementliste'.
 * \param e1 Premier élément à comparer.
 * \param e2 Second élément à comparer.
 * \return Un booléen indiquant si les deux éléments sont identiques.
 *
 * Cette fonction compare deux éléments 'Elementliste' et renvoie 'true' si tous leurs champs respectifs sont égaux.
 * Elle est utile pour vérifier l'égalité de deux arcs dans un graphe.
 */
bool cmp_elements(Elementliste e1, Elementliste e2){
    return (e1.orig == e2.orig) && (e1.dest == e2.dest) && (e1.poids == e2.poids);
}

/**
 * \brief Affiche un élément de type 'Elementliste'.
 * \param e Élément à afficher.
 * \param fp Pointeur vers un fichier (FILE) où l'élément sera affiché.
 *
 * Cette fonction affiche les détails de l'élément 'e' dans le fichier spécifié par 'fp'.
 * Elle formatte l'affichage sous la forme (origine, destination, poids).
 */
void afficher_element(Elementliste e, FILE *fp){
    fprintf(fp, "(%d, %d, %d)\n", e.orig, e.dest, e.poids); // Formatage et affichage de l'élément
}

/**
 * \brief Permet la saisie d'un élément de type 'Elementliste' par l'utilisateur.
 * \param e Pointeur vers l'élément à remplir.
 *
 * Cette fonction invite l'utilisateur à saisir les détails d'un arc (origine, destination, poids) 
 * et stocke ces informations dans l'élément pointé par 'e'.
 */
void saisie_element(Elementliste *e){
    printf("Arc ? (trois entiers séparés par des espaces)"); // Invite l'utilisateur
    scanf("%d", &(e->orig));   // Lecture du noeud d'origine
    scanf("%d", &(e->dest));   // Lecture du noeud de destination
    scanf("%d", &(e->poids));  // Lecture du poids de l'arc
}

