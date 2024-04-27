/**
 * \file Condorcet.c
 * \brief Déclarations et documentations des méthodes Condorcet
 * \date 05/12/2023
 *
 * Ce fichier contient les déclarations des méthodes liées à la méthode Condorcet,
 * telles que la recherche du vainqueur Condorcet et le calcul du gagnant selon le
 * critère minimax.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include "duel.h"
#include "utils_sd.h"
#include "global.h"

#include "lecture_csv.h"
#include "matrice.h"
#include "graph.h"
#include "condorcet.h"

/**************************************************************************************************************************************/
// Vainqueur Condorcet
/**
 * \fn char* winnerCondorcet(graph *graphe)
 * \brief Trouve le vainqueur Condorcet dans un graphe donné.
 * \param[in] graphe Pointeur vers le graphe représentant les duels entre candidats.
 * \return Le nom du vainqueur Condorcet, ou NULL si aucun vainqueur n'est trouvé.
 */
char *winnerCondorcet(graph *graphe) {
    int nbCandidats = graphe->nbSommet;
    char *winner = NULL;

    for (int i = 0; i < nbCandidats; i++) {
        if (graphe->sommets[i]->nbPredecesseur == 0)
            winner = graphe->sommets[i]->nom;
    }
    return winner;
}
/**
 * \fn void creer_t_mat_int_dyn(t_mat_int_dyn *mat, int nbRows, int nbCols)
 * \brief Crée une matrice d'entiers dynamique.
 * \param[out] mat Pointeur vers la matrice d'entiers dynamique.
 * \param[in] nbRows Nombre de lignes de la matrice.
 * \param[in] nbCols Nombre de colonnes de la matrice.
 */
void creer_t_mat_int_dyn(t_mat_int_dyn *mat, int nbRows, int nbCols) {
    mat->nbRows = nbRows;
    mat->nbCol = nbCols;
    mat->tab = malloc(nbRows * sizeof(int *));
    for (int i = 0; i < nbRows; i++) {
        mat->tab[i] = calloc(nbCols, sizeof(int));
    }
}

/**
 * \fn void construct_mat_duels_from_ballot(t_mat_char_star_dyn *mat_ballots, t_mat_int_dyn *duels_mat, int nbCandidats, FILE *outfp)
 * \brief Construit la matrice de duels à partir des bulletins de vote.
 * \param[in] mat_ballots Matrice des bulletins de vote.
 * \param[out] duels_mat Matrice des duels à construire.
 * \param[in] nbCandidats Nombre de candidats.
 * \param[in] outfp Pointeur vers le fichier de sortie.
 */

void construct_mat_duels_from_ballot(t_mat_char_star_dyn *mat_ballots, t_mat_int_dyn *duels_mat, int nbCandidats, FILE *outfp) {
    int offset = 0; // Ajustez cette valeur selon votre logique
    creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);
    for (size_t i = 0; i < nbCandidats; i++) {
        for (size_t k = 0; k < nbCandidats; k++) {
            if (i != k) {
                for (size_t numero_votant = 1; numero_votant < mat_ballots->nbRows; numero_votant++) {
                    if (atoi(mat_ballots->matrix[numero_votant][offset + i]) <
                        atoi(mat_ballots->matrix[numero_votant][offset + k])) {
                        duels_mat->tab[i][k]++;
                    }
                }
            }
        }
    }
}


/**
 * \fn void construct_mat_duels_from_csv_duels(t_mat_char_star_dyn *tabmots, t_mat_int_dyn *duels_mat, int nbCandidats, FILE *outfp)
 * \brief Construit la matrice de duels à partir d'un fichier CSV de duels.
 * \param[in] tabmots Tableau des mots lus du fichier CSV.
 * \param[out] duels_mat Matrice des duels à construire.
 * \param[in] nbCandidats Nombre de candidats.
 * \param[in] outfp Pointeur vers le fichier de sortie.
 */
void construct_mat_duels_from_csv_duels(t_mat_char_star_dyn *tabmots, t_mat_int_dyn *duels_mat, int nbCandidats, FILE *outfp) {
    creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);
    for (size_t i = 1; i < tabmots->nbRows; i++) {
        for (size_t j = 0; j < tabmots->nbCols; j++) {
            duels_mat->tab[i - 1][j] = atoi(tabmots->matrix[i][j]);
        }
    }
}

/**
 * \fn void afficher_candidats(char **noms_candidats, int nb_candidats, FILE* outfp)
 * \brief Affiche les noms des candidats.
 * \param[in] noms_candidats Tableau des noms des candidats.
 * \param[in] nb_candidats Nombre de candidats.
 * \param[in,out] outfp Pointeur vers le fichier de sortie pour l'affichage.
 */
void afficher_candidats(char **noms_candidats, int nb_candidats,FILE* outfp) {
    for (int i = 0; i < nb_candidats; i++) {
        fprintf(outfp,"Nom du candidat n°%d: %s\n", i + 1, noms_candidats[i]);
    }
    fprintf(outfp,"\n");
}
/**
 * \fn char** recupere_nom_candidats(t_mat_char_star_dyn *matrice_ballot)
 * \brief Récupère les noms des candidats à partir d'une matrice de bulletins.
 * \param[in] matrice_ballot Pointeur vers la matrice contenant les bulletins de vote.
 * \return Un tableau de chaînes de caractères contenant les noms des candidats.
 */

char **recupere_nom_candidats(t_mat_char_star_dyn *matrice_ballot) {
    int offset = 0; // Ajustez cette valeur selon votre logique
    int nbCand = matrice_ballot->nbCols - offset;
    char **noms = malloc(nbCand * sizeof(char *));

    for (int i = 0; i < nbCand; i++) {
        char *nom = matrice_ballot->matrix[0][i + offset];
        noms[i] = strdup(nom); // Copie le nom
    }

    return noms;
}

/**
 * \fn int condorcet1(t_mat_int_dyn *matriceDuels, FILE *outfp)
 * \brief Détermine le vainqueur Condorcet à partir d'une matrice de duels.
 * \param[in] matriceDuels Pointeur vers la matrice de duels entre les candidats.
 * \param[in,out] outfp Pointeur vers le fichier de sortie pour l'enregistrement des résultats.
 * \return L'indice du gagnant Condorcet, ou -1 s'il y a un conflit ou aucun gagnant.
 */
int condorcet1(t_mat_int_dyn *matriceDuels, FILE *outfp) {
    int i, j, k;
    int gagnantTrouve = -1;
    int* victoires = (int*)malloc(matriceDuels->nbRows * sizeof(int));

    // Initialisation des compteurs de victoires
    for (i = 0; i < matriceDuels->nbRows; i++) {
        victoires[i] = 0;
    }

    // Parcours de la matrice des duels
    for (i = 0; i < matriceDuels->nbRows; i++) {
        for (j = 0; j < matriceDuels->nbRows; j++) {
            if (i != j) {
                int victoireI = 0;
                int victoireJ = 0;

                // Comptage des victoires pour chaque candidat dans les duels
                for (k = 0; k < matriceDuels->nbCol; k++) {
                    if (matriceDuels->tab[i][k] > matriceDuels->tab[j][k]) {
                        victoireI++;
                    } else {
                        victoireJ++;
                    }
                }

                // Détermination du gagnant du duel
                if (victoireI > victoireJ) {
                    victoires[i]++;
                } else if (victoireJ > victoireI) {
                    victoires[j]++;
                }
            }
        }
    }

    // Vérification s'il y a un seul gagnant
    for (i = 0; i < matriceDuels->nbRows; i++) {
        if (victoires[i] == matriceDuels->nbRows - 1) {
            if (gagnantTrouve == -1) {
                // Affichage du gagnant

                //fprintf(outfp,"Le vainqueur de Condorcet est le candidat n° %d.\n", i+1 );
                gagnantTrouve = i;
            } else {
                // S'il y a déjà un gagnant, il y a un conflit
                free(victoires);
                return -1;
            }
        }
    }

    // Aucun gagnant trouvé
    free(victoires);
    return gagnantTrouve;
}


/**
 * \fn Resultats* construction_mat_duels(int option, char *filename, FILE* outfp)
 * \brief Construit la matrice de duels et prépare les résultats en fonction de l'option choisie.
 * \param[in] option Choix du mode de construction de la matrice de duels.
 * \param[in] filename Nom du fichier CSV contenant les bulletins de vote ou les duels.
 * \param[in,out] outfp Pointeur vers le fichier de sortie pour l'enregistrement des résultats.
 * \return Pointeur vers la structure Resultats contenant la matrice de duels et les noms des candidats.
 */
Resultats *construction_mat_duels(int option, char *filename, FILE* outfp) {
    Resultats *result = malloc(sizeof(Resultats));
    int nb_votants = 0, nb_candidats = 0;
    char **noms_candidats = NULL;

    t_mat_int_dyn *duels_mat = malloc(sizeof(t_mat_int_dyn));
    t_mat_char_star_dyn *mat_ballots = malloc(sizeof(t_mat_char_star_dyn));
    
    // Lecture du fichier CSV dans mat_ballots
    lireFichierCSV(filename,mat_ballots);
    nb_votants = mat_ballots->nbRows - 1;
    result->nb_votant = nb_votants;

    switch (option) {
        case 1:
            // Gestion de l'option 1
            nb_candidats = mat_ballots->nbCols - 4;
            noms_candidats = recupere_nom_candidats(mat_ballots);
            afficher_candidats(noms_candidats, nb_candidats, outfp);
            construct_mat_duels_from_ballot(mat_ballots, duels_mat, nb_candidats, NULL);
            break;
        case 2:
            // Gestion de l'option 2
            nb_candidats = mat_ballots->nbCols;
            noms_candidats = recupere_nom_candidats(mat_ballots);
            afficher_candidats(noms_candidats, nb_candidats, outfp);
            construct_mat_duels_from_csv_duels(mat_ballots, duels_mat, nb_candidats, NULL);
            break;
        default:
            // Gestion par défaut
            break;
    }

    result->duels_mat = duels_mat;
    result->nom_candidats = noms_candidats;

    return result;
}



/**
 * \fn void condorcet(char *f)
 * \brief Fonction principale pour l'exécution de la méthode Condorcet.
 * \param[in] f Nom du fichier CSV contenant les bulletins de vote ou les duels.
 */
 
void condorcet(char *f){
    t_mat_char_star_dyn *matrice;
    matrice = creer_matrice_char();
    lireFichierCSV(f, matrice);

    t_mat_int_dyn *mat_duel;
    mat_duel = construire_mat_duel(matrice);

    char **listeNomSommets;
    listeNomSommets = get_candidats(matrice);
    graph *graphe; 
    graphe = creer_graphe_de_matrice_duel(mat_duel, listeNomSommets);

    char *winner;
    winner = winnerCondorcet(graphe);
    printf("Mode de scrutin : Condorcet, %d candidats, %d votants, vainqueur condorcet = %s\n",mat_duel->nbCol, matrice->nbRows-1, winner);
}


/**************************************************************************************************************************************/
// MiniMax
/**
 * \fn int winnerMinimax(t_mat_int_dyn *mat_duel)
 * \brief Détermine le vainqueur selon la méthode Minimax dans une matrice de duels.
 * \param[in] mat_duel Pointeur vers la matrice de duels entre les candidats.
 * \return L'indice du candidat gagnant selon la méthode Minimax.
 * \details Cette fonction parcourt la matrice de duels pour trouver le candidat ayant le score Minimax le plus bas, 
 *          indiquant le candidat le plus fort selon la méthode Minimax.
 */
int winnerMinimax(t_mat_int_dyn *mat_duel){
    int minimax = scoreMaxCandidat(mat_duel, 0); 
    int indWinner = 0;
    for (int i=1; i<mat_duel->nbCol; i++) {
        if(scoreMaxCandidat(mat_duel, i) < minimax){
            minimax = scoreMaxCandidat(mat_duel, i);
            indWinner = i;
        }
    }
    return indWinner;
}

/**
 * \fn void minimax(char *f)
 * \brief Fonction principale pour l'exécution de la méthode Minimax Condorcet.
 * \param[in] f Nom du fichier CSV contenant les bulletins de vote ou les duels.
 * \details Cette fonction lit les données de vote à partir d'un fichier CSV, construit une matrice de duels, 
 *          détermine le gagnant Minimax en utilisant cette matrice, et affiche les résultats.
 */

void minimax(char *f){
    
    t_mat_char_star_dyn *matrice;
    matrice = creer_matrice_char();
    lireFichierCSV(f, matrice);
    
    t_mat_int_dyn *mat_duel;
    mat_duel = construire_mat_duel(matrice);

    char **listeNomSommets;
    listeNomSommets = get_candidats(matrice);

    int indWinner = winnerMinimax(mat_duel);

    printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n",mat_duel->nbCol, matrice->nbRows-1, listeNomSommets[indWinner]);

}

