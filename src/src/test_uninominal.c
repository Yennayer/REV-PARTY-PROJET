#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "global.h"
#include "matrice.h"
#include "uninominales.h"
#include "lecture_csv.h"

int main(int argc, char const *argv[])
{
    // Test arguments valides
    if (argc != 2) {
        fprintf(stderr, "Usage: %s nom_fichier\n", argv[0]);
        exit(1);
    }
    // Récupération du nom du fichier CSV
    char fileName[100];
    strcpy(fileName,argv[1]);

    // Lecture et Stockage du fichier dans la matrice
    t_mat_char_star_dyn *matrice;
    matrice = creer_matrice_char();
    lireFichierCSV(fileName, matrice);

    int sommeColonnes[MAX_COLUMNS - 4];

    calculerSommecolonnes(matrice, sommeColonnes); // Passer 'mat' directement

    for (int i = 0; i < matrice->nbCols - 4; i++) {
        printf("Somme colonne %d: %d\n", i + 5, sommeColonnes[i]);
    }

    int max = trouverColonneMax(matrice);
    printf("%d\n", max);
    afficher_vainqueur(matrice);
    printf("\n");
    
    afficherResultatsDeuxTours(matrice);

    return 0;
}

// Pour compiler 
// matrice.c lecture_csv.c uninominales.c test_uninominal.c -o test
// .test + chemin vers le fichier csv