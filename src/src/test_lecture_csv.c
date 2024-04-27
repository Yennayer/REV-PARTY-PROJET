#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
#include "matrice.h"


int main() {
    t_mat_char_star_dyn *matrice;
    matrice = creer_matrice_char();

    char nameFile[100];
    printf("Veuillez saisir le nom fichier CSV( exemple : fichier.csv ) : ");
    scanf("%s", nameFile);


    lireFichierCSV(nameFile, matrice);
    print_matrice_char(matrice);
    printf("t nb rows = %d\n", matrice->nbRows);
    printf("t nb cols = %d\n", matrice->nbCols);
    return 0;
}