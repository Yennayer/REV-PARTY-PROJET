#include "uninominales.h"
#include "matrice.h"

void calculerSommecolonnes(const t_mat_char_star_dyn* matrice, int sommeColonnes[]) {
    // Initialiser les sommes à 0
    for (int col = 4; col < matrice->nbCols; col++) {
        sommeColonnes[col - 4] = 0;
    }

    // Calculer la somme pour chaque colonne pertinente
    for (int col = 4; col < matrice->nbCols; col++) {
        for (int row = 1; row < matrice->nbRows; row++) {
            sommeColonnes[col - 4] += atoi(matrice->matrix[row][col]);
        }
    }
}

int trouverColonneMax(t_mat_char_star_dyn *mat) {
    int sommeColonnes[MAX_COLUMNS - 4] = {0};

    // Calculer la somme des colonnes
    calculerSommecolonnes(mat, sommeColonnes);

    int maxSum = sommeColonnes[0];
    int maxCol = 0;

    // Trouver la colonne avec la somme maximale
    for (int i = 1; i < mat->nbCols - 4; i++) {
        if (sommeColonnes[i] > maxSum) {
            maxSum = sommeColonnes[i];
            maxCol = i;
        }
    }
    // Retourner l'indice de la colonne (ajusté pour l'affichage, en commençant à 5)
    return maxCol + 5;
}

void afficher_vainqueur(t_mat_char_star_dyn *mat) {
    int sommeColonnes[MAX_COLUMNS - 4];
    calculerSommecolonnes(mat, sommeColonnes);

    int maxCol = trouverColonneMax(mat) - 5; // Ajuster pour obtenir l'index dans sommeColonnes
    int totalVotesTousCandidats = 0;

    // Calculer la somme totale des votes pour tous les candidats
    for (int i = 0; i < mat->nbCols - 4; i++) {
        totalVotesTousCandidats += sommeColonnes[i];
    }

    // Calculer le pourcentage de votes pour le vainqueur par rapport à la somme totale des votes
    double pourcentage = (totalVotesTousCandidats > 0) ? (double)sommeColonnes[maxCol] / totalVotesTousCandidats * 100 : 0;

    // Afficher les résultats
    printf("Mode de scrutin : uninominale à un tour, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
           mat->nbCols - 4, // Nombre de candidats
           mat->nbRows - 1, // Nombre total de votants (lignes moins l'en-tête)
           mat->matrix[0][maxCol + 4], // Nom du vainqueur
           pourcentage);    // Pourcentage des votes pour le vainqueur
}


void calculerDeuxPremiers(t_mat_char_star_dyn *mat, int *premier, int *second) {
    int sommeColonnes[MAX_COLUMNS - 4] = {0};
    calculerSommecolonnes(mat, sommeColonnes);

    *premier = 0;
    *second = (mat->nbCols > 5) ? 1 : -1; // -1 si moins de deux candidats

    // Trouver les deux premiers candidats
    for (int i = 1; i < mat->nbCols - 4; i++) {
        if (sommeColonnes[i] > sommeColonnes[*premier]) {
            *second = *premier;
            *premier = i;
        } else if (*second == -1 || sommeColonnes[i] > sommeColonnes[*second]) {
            *second = i;
        }
    }

    // Ajuster pour l'affichage
    *premier += 5;
    *second += 5;
}

// Assurez-vous d'inclure les définitions des fonctions existantes et des structures nécessaires ici

void afficherResultatsDeuxTours(t_mat_char_star_dyn *mat) {
    int premier, second;
    calculerDeuxPremiers(mat, &premier, &second);

    int sommeColonnes[MAX_COLUMNS - 4] = {0};
    calculerSommecolonnes(mat, sommeColonnes);

    int totalVotesTousCandidats = 0;
    for (int i = 0; i < mat->nbCols - 4; i++) {
        totalVotesTousCandidats += sommeColonnes[i];
    }

    double pourcentagePremier = (double)sommeColonnes[premier - 5] / totalVotesTousCandidats * 100;
    double pourcentageSecond = (double)sommeColonnes[second - 5] / totalVotesTousCandidats * 100;

    // Affichage des résultats du premier tour pour les deux premiers candidats
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
           mat->nbCols - 4, mat->nbRows - 1, mat->matrix[0][premier], pourcentagePremier);
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
           mat->nbCols - 4, mat->nbRows - 1, mat->matrix[0][second], pourcentageSecond);

    // Déterminer le vainqueur du second tour
    int vainqueur = (premier > second) ? premier : second;
    double pourcentage = ((double)(premier > second ? premier : second) / (mat->nbRows - 1)) * 100;

    // Affichage des résultats du second tour
    printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
           mat->nbRows - 1, mat->matrix[0][vainqueur], pourcentage);
}
