/**
 * @file        verifMyVote.c
 *
 * @brief       Contient les fonctions de vérifications
 * @author      BENAMEUR Yennayer <yennayer.benameur@univ-tlse3.fr> Groupe E9
 * @date        16/10/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Csv/matrice.h"
#include "Sha256/sha256.h"
#include "Sha256/sha256_utils.h"
#include "Csv/lecture_csv.h"

#define STRLONG 100
#define MAX 1000

/**
 * @brief Conversion d'une chaine de caractères qui est en héxadécimal en chaine de caractère binaire
 * Cette fonction convertit chaque caractère lu en héxadécimal en binaire '\0'.
 * @param hexa chaîne de caractères.
 * @return Un pointeur vers la chaîne de caractères binaire
 */
char* hexaToBinary(char *hexa) {
    char* binarynum = (char*)malloc(32 + 1);
    long int i = 0;

    while (hexa[i])
    {
        switch (hexa[i])
        {
        case '0':
            strcat(binarynum, "0000");break;
        case '1':
            strcat(binarynum, "0001");break;
        case '2':
            strcat(binarynum, "0010");break;
        case '3':
            strcat(binarynum, "0011");break;
        case '4':
            strcat(binarynum, "0100");break;
        case '5':
            strcat(binarynum, "0101");break;
        case '6':
            strcat(binarynum, "0110");break;
        case '7':
            strcat(binarynum, "0111");break;
        case '8':
            strcat(binarynum, "1000");break;
        case '9':
            strcat(binarynum, "1001");break;
        case 'A':
            strcat(binarynum, "1010");break;
        case 'B':
            strcat(binarynum, "1011");break;
        case 'C':
            strcat(binarynum, "1100");break;
        case 'D':
            strcat(binarynum, "1101");break;
        case 'E':
            strcat(binarynum, "1110");break;
        case 'F':
            strcat(binarynum, "1111");break;
        case 'a':
            strcat(binarynum, "1010");break;
        case 'b':
            strcat(binarynum, "1011");break;
        case 'c':
            strcat(binarynum, "1100");break;
        case 'd':
            strcat(binarynum, "1101");break;
        case 'e':
            strcat(binarynum, "1110");break;
        case 'f':
            strcat(binarynum, "1111");break;
        default:
            printf("\n Invalid hexa digit %c ", hexa[i]);
            //return 0;
        }
        i++;
    }
    return binarynum;
}

/**
 * @brief Cette fonction reçoie le NOM PRENOM+CLE et utilise l'algorithme SHA256 pour hasher la chaine
 *
 * @param chaineComplete
 * @return le hash de la chaine reçue en paramètres
 */
char* hashChaine(char * chaineComplete) {

    int bufferSize = SHA256_BLOCK_SIZE;

    char* hashRes = (char*)malloc(bufferSize*2 + 1);

    sha256ofString((BYTE *)chaineComplete, hashRes); // hashRes contient maintenant le hash de l'item
    // Renvoyer le hash
    return hashRes;
}

/**
 * @brief Cette fontion vérifie si le format du Nom est correct
 * @param nom
 * @return 1 si c'est bon, 0 dans le cas contraire
 */
int bonFormatNom(const char *nom) {
    while (*nom) {
        if (!isupper(*nom)) {
            return 0; // Retourne 0 si un caractère n'est pas en majuscule
        }
        nom++;
    }
    return 1; // Retourne 1 si tous les caractères sont en majuscule
}

/**
 * @brief Cette fontion vérifie si le format du Prenom est correct
 * @param prenom
 * @return 1 si c'est bon, 0 dans le cas contraire
 */
int bonFormatPrenom(const char *prenom) {
    if (prenom[0] != '\0' && isupper(prenom[0])) {
        for (int i = 1; prenom[i] != '\0'; i++) {
            if (!islower(prenom[i])) {
                return 0; // Le reste des caractères devrait être en minuscule
            }
        }
        return 1; // Le prénom est au bon format
    }
    return 0; // Le premier caractère n'est pas en majuscule
}

/**
 * @brief Cette fontion demande à l'utilisateur de saisir le nom en vérifiant le format
 * @param nom
 * @return stocke le nom dans la chaine de caractère passée en paramètres
 */
void checkNom(char *nom) {
    int bonFormat = 0;
    while (!bonFormat) {
        printf("Veuillez saisir le nom en MAJUSCULE : ");
        scanf("%s", nom);
        if (nom[strlen(nom) - 1] == '\n') {
            nom[strlen(nom) - 1] = '\0'; // Supprime le saut de ligne s'il est présent
        }
        bonFormat = bonFormatNom(nom);
        if (!bonFormat) {
            printf("Format Incorrect. Veuillez ressaisir votre nom correctement (EN MAJUSCULE).\n");
        }
    }
}

/**
 * @brief Cette fontion demande à l'utilisateur de saisir le prenom en vérifiant le format
 * @param prenom
 * @return stocke le prenom dans la chaine de caractère passée en paramètres
 */
void checkPrenom(char *prenom) {
    int bonFormat = 0;

    while (!bonFormat) {
        printf("Veuillez saisir votre prénom : ");
        scanf("%s", prenom);

        bonFormat = bonFormatPrenom(prenom);

        if (!bonFormat) {
            printf("Format Incorrect. Veuillez ressaisir votre prénom correctement.\n");
        }
    }
}

/**
 * @brief Cette fontion cherche le hash dans la matrice et enregistre la ligne et la colonne du hash s'il est trouvé
 * @param matrice/hash/ligne/colonne
 * @return Stocke la ligne et la colonne par pointeur
 */
void searchChaine(t_mat_char_star_dyn *matrice, char *hash, int *ligne, int *colonne) {
    int hashFound = 0;

    for (int i = 0; i < matrice->nbRows && hashFound == 0; i++) {
        for (int j = 0; j < matrice->nbCols && hashFound == 0; j++) {
            if (strcmp(hash, matrice->matrix[i][j]) == 0) {
                // je sauvegarde la ligne et la colonne
                hashFound = 1;
                *ligne = i;
                *colonne = j;
            }
        }
    }
}

/**
 * @brief Cette fontion affiche le résultat du vote
 * @param matrice/ligne ( ligne = ligne où se trouve le hash )
 * @return affiche le résultat du vote
 */
void afficherVote(t_mat_char_star_dyn *matrice, int ligne) {
    if (ligne <= 0 || ligne >= matrice->nbRows) {
        printf("Résultat Du Vote Non Trouvé\n");
        exit(1);
    }

    printf("Trouvé, voici le vote\n");

    // Afficher le vote pour chaque candidat
    // for (int i = 4; i < 14; i++)
    for (int i = 4; i < matrice->nbCols; i++) {
        printf("%s %s \n", matrice->matrix[0][i], matrice->matrix[ligne][i]);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    // Déclarations des variables
    t_mat_char_star_dyn *matriceCSV;
    matriceCSV = creer_matrice_char();

    int ligne;
    int colonne;

    char nomElecteur[STRLONG];
    char prenomElecteur[STRLONG];
    char temp[STRLONG];
    char nameFile[STRLONG];
    char key[STRLONG];
    char *hash;

    char *convertHash;

    char *chaineComplete = malloc(STRLONG * sizeof(char));  /**< contiendra la chaîne à hasher */

    // Saisie d'informations

    checkNom(nomElecteur);
    checkPrenom(prenomElecteur);
    printf("Veuillez saisir la clef secrète : ");
    scanf("%s", key);

    // Saisie du nom du fichier de vote
    printf("Veuillez saisir le nom fichier de ballots ( exemple : fichier.csv ) : ");
    scanf("%s", nameFile);

    // Concatener Nom + Espace + Prenom + Cle
    sprintf(chaineComplete, "%s %s%s",nomElecteur,prenomElecteur,key);
    printf("Chaine = %s\n", chaineComplete);
    
    // Hasher la chaine concaténée
    hash = hashChaine(chaineComplete);

    // Lire le fichier CSV en le stockant dans la matrice
    lireFichierCSV(nameFile, matriceCSV);

    // chercher le hash dans la matrice
    searchChaine(matriceCSV, hash, &ligne, &colonne);

    printf("Le hash est : %s\n", hash);

    printf("t nb rows = %d\n", matriceCSV->nbRows);
    printf("t nb cols = %d\n", matriceCSV->nbCols);

    // Afficher le résultat du vote
    afficherVote(matriceCSV, ligne);

    return 0;
}

// gcc verif_my_vote.c Sha256/sha256.c Sha256/sha256_utils.c Csv/lecture_csv.c Csv/matrice.c -o test 

// zrrArisZSIO3