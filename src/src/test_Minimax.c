/**
 * \file testCondorcet.c
 * \brief Test Méthode Vainqueur Condorcet
 * \date 09/12/2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

#include "lecture_csv.h"
#include "matrice.h"
#include "graph.h"
#include "condorcet.h"


int main(int argc, char const *argv[]) {
    // Test arguments valides
    if (argc != 2) {
        fprintf(stderr, "Usage: %s nom_fichier\n", argv[0]);
        exit(1);
    }
    // Récupération du nom du fichier CSV
    char fileName[100];
    strcpy(fileName,argv[1]);
    
    // char *f = "fich_tests/testM.csv";
    
    minimax(fileName);
    return 0;
}


// Pour compiler
// gcc test_Minimax.c condorcet.c graph.c lecture_csv.c matrice.c -o test
// .test + chemin vers le fichier csv