#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <execinfo.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include "matrice.h"
#include "global.h"

// Matrice CSV
t_mat_char_star_dyn *creer_matrice_char() {
    t_mat_char_star_dyn *new_matrix = malloc(sizeof(t_mat_char_star_dyn));
    new_matrix->nbRows = 0;
    new_matrix->nbCols = 0;
    new_matrix->nb_elem = 0; 
    return new_matrix;
}


void supprimer_matrice_char(t_mat_char_star_dyn *matrice) {
    for (int i = 0; i < matrice->nbRows; i++) {
        for (int j = 0; j < matrice->nbCols; j++) {
            free(matrice->matrix[i][j]);
        }
    }
    free(matrice->matrix[0][0]);
    free(matrice);
}


int get_nb_colonnes(t_mat_char_star_dyn *matrice) {
    return matrice->nbCols;
}


int get_nb_lignes(t_mat_char_star_dyn *matrice) {
    return matrice->nbRows;
}

int est_matrice_vide(t_mat_char_star_dyn *matrice) {
    return matrice->nb_elem == 0;
}

char **get_candidats(t_mat_char_star_dyn *matrice) {
    char **candidats = malloc((matrice->nbCols - 4) * sizeof(char *));
    int taille = matrice->nbCols;
    for (int i = 4; i < taille; i++) {
        candidats[i - 4] = strdup(matrice->matrix[0][i]);
    }
    return candidats;
}


void print_matrice_char(const t_mat_char_star_dyn *matrice) {
    for (int i=0; i<matrice->nbRows; i++) {
        for (int j=0; j<matrice->nbCols; j++) {
            printf("  %s ", matrice->matrix[i][j]);
        }
        printf("\n");
    }
}
/****************************************************************************************************************************/

// Matrice Duel

t_mat_int_dyn *creer_matrice_int(int ligne, int colonne) {
    t_mat_int_dyn *matrice = malloc(sizeof(t_mat_int_dyn));
    matrice->nbRows = ligne;
    matrice->nbCol = colonne;
    matrice->tab = (int **)malloc(ligne * sizeof(int *));

    for (int i = 0; i < ligne; i++) {
        matrice->tab[i] = (int *) malloc(colonne * sizeof(int));

        // Initialiser chaque élément à 0
        for (int j = 0; j < colonne; j++) {
            matrice->tab[i][j] = 0;
        }
    }
    return matrice;
}


t_mat_int_dyn *construire_mat_duel(t_mat_char_star_dyn *matrice) {
    int ligne = matrice->nbRows;
    int colonne = matrice->nbCols, val1, val2;
    t_mat_int_dyn *duel_m = creer_matrice_int(colonne- 4, colonne - 4);
    if (!est_matrice_vide(matrice)) {
        for (int i = 1; i < matrice->nbRows; i++) {
            for (int j = 4; j < colonne; j++) {
                val1 = atoi(matrice->matrix[i][j]);
                for (int k = j + 1; k < colonne; k++) {
                    val2 = atoi(matrice->matrix[i][k]);
                    if (val1 > val2) {
                        duel_m->tab[k - 4][j - 4]++;
                    } else if (val1 < val2) {
                        duel_m->tab[j - 4][k - 4]++;
                    } else {
                        duel_m->tab[k - 4][j - 4]++;
                        duel_m->tab[j - 4][k - 4]++;
                    }
                }
            }
        }
    }
    return duel_m;
}


t_mat_int_dyn *mat_char_to_mat_duel(t_mat_char_star_dyn *matrice) {
    int ligne = matrice->nbRows;
    int colonne = matrice->nbCols;
    t_mat_int_dyn *mat_duel = creer_matrice_int(colonne, colonne);
    for (int i = 1; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            mat_duel->tab[i][j] = atoi(matrice->matrix[i][j]);
            printf("%s ", matrice->matrix[i][j]);
        }
    }
    return mat_duel;
}


int scoreMaxCandidat(t_mat_int_dyn *mat_duel, int iCandidat){
    int maxScore = mat_duel->tab[0][iCandidat];
    for (int i=1; i<mat_duel->nbRows; i++){
        if(i != iCandidat){
            if(mat_duel->tab[i][iCandidat]>maxScore){
                maxScore = mat_duel->tab[i][iCandidat]; 
            }
        }
    }
    return maxScore; 
}

// Fonction pour initialiser une matrice dynamique
void initialiserMatrice(MatriceDynamique *matriceDyn, int nbCandidats, int nbDuels) {
    matriceDyn->nbCandidats = nbCandidats;
    matriceDyn->nbDuels = nbDuels;

    // Allocation de la mémoire pour la matrice
    matriceDyn->matrice = (int ***)malloc(nbCandidats * sizeof(int **));
    for (int i = 0; i < nbCandidats; i++) {
        matriceDyn->matrice[i] = (int **)malloc(nbCandidats * sizeof(int *));
        for (int j = 0; j < 2; j++) {
            matriceDyn->matrice[i][j] = (int *)malloc(nbDuels * sizeof(int));
        }
    }
}

// Fonction pour libérer la mémoire de la matrice dynamique
void libererMatrice(MatriceDynamique *matriceDyn) {
    for (int i = 0; i < matriceDyn->nbCandidats; i++) {
        for (int j = 0; j < matriceDyn->nbCandidats; j++) {
            free(matriceDyn->matrice[i][j]);
        }
        free(matriceDyn->matrice[i]);
    }
    free(matriceDyn->matrice);
}


int NB_DUELS = NB_CANDIDAT - 1;  // Initialisation de la constante
const char *burgers[10] = {"Burger Black Pepper", "Burger Sud-Ouest", "Thai Burger", "Veggie Burger", "Fire cracker", "Roma", "Crispy", "Cheese Burger", "Burger surprise", "Country"};  // Initialisation de la constante

void print_matrice_int(t_mat_int_dyn *mat_duel) {
    int **T = mat_duel->tab;
    int L = mat_duel->nbRows;
    int C = mat_duel->nbCol;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%5d ", T[i][j]);
        }
        printf("\n");
    }
}

void supprimer_matrice_int(t_mat_int_dyn *mat_duel) {
    int **T = mat_duel->tab;
    int ligne = mat_duel->nbRows;

    for (int i = 0; i < ligne; i++) {
        free(T[i]);
    }
    free(T);
    free(mat_duel);
}
