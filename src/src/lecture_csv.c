/**
 * \file lecture_csv.c
 * \brief Fonctions pour lire des données à partir de fichiers CSV et les stocker dans des structures appropriées.
 * \date 19/10/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

/**
 * \brief Ouvre un fichier CSV et stocke son contenu dans une matrice.
 * \param nomFichier Nom du fichier CSV à lire.
 * \param matrice Pointeur vers la matrice dans laquelle les données seront stockées.
 *
 * Cette fonction lit chaque ligne du fichier CSV, découpe chaque ligne en éléments séparés par des virgules,
 * et stocke ces éléments dans la matrice fournie. Elle gère également la mémoire et les erreurs d'ouverture de fichier.
 */
void lireFichierCSV(char* nomFichier, t_mat_char_star_dyn* matrice) {
    FILE* fichier;
    char buffer[1024]; // Pour stocker chaque ligne lue depuis le fichier

    int ligne = 0;
    int col = 0;
    int nbElem = 0;
    fichier = fopen(nomFichier, "r"); // Ouvrir le fichier CSV en mode lecture
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(2);
    }
    
    
    // Lire chaque ligne du fichier
    while (fgets(buffer, sizeof(buffer), fichier) && ligne < MAX_LINE) {
        col = 0;
        int length = strlen(buffer);
        if (buffer[length -1] == '\n')
            buffer[--length] = '\0';
        // Découper la ligne en tokens (éléments séparés par des virgules)
        char* token = strtok(buffer, ",");
        while (token != NULL) {
            // Allouer de la mémoire pour stocker chaque élément
            strcpy(matrice->matrix[ligne][col], token);
            col++;
            // passer au token suivant
            token = strtok(NULL, ",");
            nbElem++;
            
        }

        ligne++;
    }


    matrice->nbRows = ligne;
    matrice->nbCols = col;
    matrice->nb_elem = nbElem;
    // Fermer le fichier après lecture
    fclose(fichier);
}
/**
 * \brief deuxieme lecteur :Lit un fichier CSV contenant les votes des électeurs et les stocke dans un tableau de structures voteElecteur.
 * \param nomFichier Nom du fichier CSV à lire.
 * \param v_elect Pointeur vers un tableau de structures voteElecteur.
 * \param nb_elect Pointeur vers la structure nbElecteurs indiquant le nombre total d'électeurs.
 *
 * Cette fonction lit le fichier CSV ligne par ligne, découpe chaque ligne en tokens et remplit le tableau v_elect
 * avec des structures voteElecteur correspondantes. Chaque voteElecteur contient des informations détaillées sur le vote de chaque électeur.
 */
void lireFichierCSV_vote(const char *nomFichier, voteElecteur **v_elect,nbElecteurs* nb_elect) {
    FILE *fichier; // Déclaration d'un pointeur de type FILE pour le fichier.
    int ligne_count = 0; // Compteur pour le nombre de lignes (électeurs) lues.
    char buffer[1000]; // Buffer pour stocker temporairement chaque ligne lue du fichier.

    // Tente d'ouvrir le fichier en mode lecture. Si échec, affiche une erreur et quitte.
    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    // Ignore la première ligne du fichier (souvent les en-têtes).
    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        fprintf(stderr, "Fichier vide.\n"); // Si le fichier est vide, affiche un message d'erreur et quitte.
        fclose(fichier); // Ferme le fichier.
        exit(1);
    }
    
    // Lecture des lignes
    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, ",");
        int col_count = 0;
        v_elect[ligne_count] = malloc(sizeof(voteElecteur)); 
        while (token != NULL && col_count < 14) {
            switch (col_count) {
                case 0:
                    v_elect[ligne_count]->reponse = atoi(token);
                    break;
                case 1:
                    v_elect[ligne_count]->date = strdup(token);
                    break;
                case 2:
                    v_elect[ligne_count]->cours = strdup(token);

                    break;
                case 3:
                    v_elect[ligne_count]->hash = strdup(token);
                    break;
                default:
                    v_elect[ligne_count]->votes_electeur[col_count-4] = atoi(token);
                    break;
            }
            token = strtok(NULL, ",");
            col_count++;
        }
        ligne_count++;
    }
    nb_elect->nb_electeur = ligne_count;
    fclose(fichier);

}



/**
 * \brief Lit un fichier CSV contenant les informations des électeurs et les stocke dans un tableau de structures electeur.
 * \param nomFichier Nom du fichier CSV à lire.
 * \param electeurs Pointeur vers un tableau de structures electeur.
 * \param nb_elect Pointeur vers la structure nbElecteurs indiquant le nombre total d'électeurs.
 *
 * Cette fonction lit le fichier CSV ligne par ligne, découpe chaque ligne en tokens et remplit le tableau electeurs
 * avec des structures electeur correspondantes. Chaque electeur contient le numéro et la clé de chaque électeur.
 */
void lireFichierCSV_electeur(const char* nomFichier, electeur **electeurs,nbElecteurs* nb_elect) {
    // Déclaration de variables
    FILE *fichier; // Pointeur vers le fichier à lire
    int ligne_count = 0; // Compteur pour le nombre de lignes lues
    char buffer[1000]; // Buffer pour stocker chaque ligne lue

    // Tente d'ouvrir le fichier en mode lecture et vérifie si l'ouverture a réussi
    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur d'ouverture du fichier"); // Affiche un message d'erreur si l'ouverture échoue
        exit(1); // Quitte le programme en cas d'échec
    }
// Ignore la première ligne du fichier (souvent utilisée pour les en-têtes)
    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        fprintf(stderr, "Fichier vide.\n"); // Affiche un message si le fichier est vide
        fclose(fichier); // Ferme le fichier
        exit(1); // Quitte le programme
    }
    
    // Boucle pour lire chaque ligne du fichier
    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, " "); // Sépare la ligne lue en tokens (éléments)
        int col_count = 0; // Compteur pour les colonnes (éléments) de chaque ligne
        electeurs[ligne_count] = malloc(sizeof(electeur)); // Alloue de la mémoire pour chaque nouvel électeur

        // Boucle pour traiter chaque token (élément) de la ligne
        while (token != NULL && col_count < 2) { // Limite à deux colonnes (éléments)
            switch (col_count) {
                case 0:
                    // Premier élément: numéro de l'électeur
                    electeurs[ligne_count]->num_electeur = atoi(token);
                    break;
                case 1:
                    // Deuxième élément: clé de l'électeur
                    electeurs[ligne_count]->clef = strdup(token);
                    break;
                default:
                    break; // Ignorer les colonnes supplémentaires
            }
            token = strtok(NULL, " "); // Passe au token suivant
            col_count++; // Incrémente le compteur de colonnes
        }
        ligne_count++; // Incrémente le compteur de lignes
    }
    nb_elect->nb_electeur = ligne_count; // Met à jour le nombre total d'électeurs lus
    fclose(fichier); // Ferme le fichier après la lecture
}
