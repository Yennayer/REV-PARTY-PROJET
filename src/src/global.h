
/**
 * \file global.h
 * \brief Fichier d'en-tête global contenant les définitions des constantes, des structures et des types utilisés dans l'ensemble du projet.
 */

#ifndef REV_PARTY_GLOBAL_H
#define REV_PARTY_GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// Définitions des constantes pour les dimensions maximales

#define MAX_ROWS 500
#define MAX_COLUMNS 500
#define MAX_STRING_SIZE 200
#define MAX_LINE 500 // Nombre maximal de lignes dans la matrice
#define MAX_COLS 500   // Nombre maximal de colonnes dans la matrice (10 candidats +)
#define MAX_FILE_NAME 256
#define SIZE_INT_DISPLAY 3
#define MAX_FILE_NAME 256




// Structure pour une matrice de chaînes de caractères

typedef struct s_mat_char_dyn{
    char matrix[MAX_ROWS][MAX_COLUMNS][MAX_STRING_SIZE];
    int nbRows;
    int nbCols;
    int nb_elem;
} t_mat_char_star_dyn;

// Structure pour une matrice d'entiers dynamique

typedef struct s_mat_dyn{
    int ** tab;
    int nbRows;
    int nbCol;
} t_mat_int_dyn;

typedef struct {
    int orig;  /*Noeud d'origine de l'arc. */
    int dest;  /* Noeud de destination de l'arc. */
    int poids; /* Poids de l'arc. */
} t_arc_p;

typedef struct s_tab_dyn{
    int * tab;
    int dim;
} t_tab_int_dyn;

/**
 * @struct Resultats
 * @brief Structure pour stocker la matrice des duels, le tableau contenant le nom des candidats et le nombre de votants.
 */
 // Structure pour stocker les résultats incluant la matrice des duels et les noms des candidats
typedef struct {
    t_mat_int_dyn *duels_mat;   /*Matrice des duels*/
    char **nom_candidats;       /*Tableau des noms des candidats*/
    int nb_votant;              /*Nombre de votants*/
} Resultats;

/**
 * @struct t_mat_char_star_dyn_off
 * @brief Structure pour une matrice tridimensionnelle de chaînes de caractères avec décalage.
 */
typedef struct {
    char ***data; 
    int rows;     
    int cols;     
    int offset;   
} t_mat_char_star_dyn_off;


/*----------------------------VARS GLOBALS----------------------------*/
#define NB_CANDIDAT 10
extern int NB_DUELS;  // Déclaration de la constante
extern const char *burgers[10];  // Déclaration de la constante
/*--------------------------------------------------------------------*/

/**
 * \struct voteElecteur
 * \brief Structure représentant un électeur pour le jugement majoritaire.
 *
 * Cette structure stocke les informations relatives à un électeur, y compris ses votes,
 * une réponse spécifique (si nécessaire), ainsi que des métadonnées comme la date, le cours 
 * et un hash pour l'identification ou la vérification.
 */
typedef struct {
    int votes_electeur[10]; /*!< Tableau stockant les votes de l'électeur, limité à 10 choix. */
    int reponse;            /*!< Réponse spécifique de l'électeur, si nécessaire. */
    char *date;             /*!< Date du vote. */
    char *cours;            /*!< Informations sur le cours lié au vote. */
    char *hash;             /*!< Hash pour l'identification ou la vérification. */
} voteElecteur;

/**
 * \struct electeur
 * \brief Structure pour stocker les informations clés d'un électeur.
 *
 * Cette structure contient une clé unique pour chaque électeur et un numéro d'identification.
 */
typedef struct {
    char *clef;       /*!< Clé unique de l'électeur. */
    int num_electeur; /*!< Numéro d'identification de l'électeur. */
} electeur;

/**
 * \enum e_module
 * \brief Énumération des différents modules ou méthodes de vote.
 *
 * Cette énumération liste les différents modules ou méthodes de vote qui peuvent être utilisés,
 * comme UNI1, UNI2, MINIMAX, etc.
 */
typedef enum e_module {
    UNI1 = 1, /*!< Module UNI1. */
    UNI2,     /*!< Module UNI2. */
    MINIMAX,  /*!< Module MINIMAX. */
    RANGEMENT,/*!< Module RANGEMENT. */
    SCHULZE,  /*!< Module SCHULZE. */
    JUGEMENT_MAJORITAIRE, /*!< Module JUGEMENT_MAJORITAIRE. */
    ALL       /*!< Tous les modules. */
} Module;

/**
 * \struct nbElecteurs
 * \brief Structure pour stocker le nombre d'électeurs.
 *
 * Cette structure est utilisée pour maintenir le compte du nombre total d'électeurs
 * participant à un vote.
 */
typedef struct {
    int nb_electeur; /*!< Nombre total d'électeurs. */
} nbElecteurs;


/**
 * \struct MatriceDynamique
 * \brief Structure représentant une matrice dynamique pour les duels de candidats.
 *
 * Cette structure stocke les informations relatives aux duels entre candidats, y compris
 * le nombre de candidats, le nombre de duels, et une matrice tridimensionnelle pour représenter
 * les résultats de ces duels.
 */
typedef struct {
    int nbCandidats; /*!< Nombre de candidats. */
    int nbDuels;     /*!< Nombre de duels entre candidats. */
    int ***matrice;  /*!< Matrice tridimensionnelle représentant les duels. */
} MatriceDynamique;


/**
 * \struct filee_t
 * \brief Structure pour gérer les informations relatives à un fichier de vote.
 *
 * Cette structure stocke les détails d'un fichier de vote, y compris le module de vote utilisé,
 *  le nom du fichier de vote, et un booléen indiquant si un fichier de log
 * est présent.
 */
typedef struct filee_t {
    Module module;        /* Module appelé, enum Module */
    char file_name[MAX_FILE_NAME];      /* Nom du fichier de vote */
    bool has_log_file;    
    char log_file[MAX_FILE_NAME];       /* Potentiel nom du fichier de log */
} Filee;



#endif //REV_PARTY_GLOBAL_H
