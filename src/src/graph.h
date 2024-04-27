#ifndef GRAPH_H
#define GRAPH_H

#include "matrice.h"
#include "global.h"

/**
 * @file graph.h
 * @brief Définition des structures et des fonctions pour la manipulation de graphes.
 */


/**
 * @struct sommet
 * @brief Structure représentant un sommet dans le graphe.
 */
typedef struct sommet {
    char *nom; /**< Nom du sommet. */
    int nbPredecesseur; /**< Nombre de prédécesseurs. */
    int nbSuccesseur; /**< Nombre de successeurs. */
    // Ajoutez d'autres champs si nécessaire
} sommet;

/**
 * @struct arc
 * @brief Structure représentant un arc dans le graphe.
 */
typedef struct arc {
    sommet *arrivee; /**< Sommet d'arrivée de l'arc. */
    sommet *depart; /**< Sommet de départ de l'arc. */
    int poids; /**< Poids de l'arc. */
} arc;

/**
 * @struct graph
 * @brief Structure représentant un graphe.
 */
typedef struct graph {
    sommet **sommets; /**< Liste des sommets du graphe. */
    arc **arcs; /**< Liste des arcs du graphe. */
    int nbSommet; /**< Nombre de sommets dans le graphe. */
    int nbArc; /**< Nombre d'arcs dans le graphe. */
} graph;


/**
 * @brief Crée et renvoie un sommet avec le nom spécifié.
 * @param nom Le nom du sommet.
 * @return Un pointeur vers le sommet créé.
 */
sommet *creer_sommet(char *nom);


/**
 * @brief Crée et renvoie un arc entre les sommets spécifiés avec le poids spécifié.
 * @param arrivee Sommet d'arrivée.
 * @param depart Sommet de départ.
 * @param poids Poids de l'arc.
 * @return Un pointeur vers l'arc créé.
 */
arc *creer_arc(sommet *arrivee, sommet *depart, int poids);

/**
 * @brief Crée et renvoie un graphe vide.
 * @return Un pointeur vers le graphe créé.
 */
graph *creer_graph();

/**
 * @brief Ajoute un sommet au graphe.
 * @param graphe Le graphe auquel ajouter le sommet.
 * @param somm Le sommet à ajouter.
 * @return Le nombre total de sommets après l'ajout.
 */
int add_sommet(graph *graphe, sommet *somm);

/**
 * @brief Ajoute un arc au graphe.
 * @param graphe Le graphe auquel ajouter l'arc.
 * @param a L'arc à ajouter.
 * @return Le nombre total d'arcs après l'ajout.
 */
int add_arc(graph *graphe, arc *a);

/**
 * @brief Recherche et renvoie l'arc avec le poids minimum dans le graphe.
 * @param graphe Le graphe à analyser.
 * @return Un pointeur vers l'arc avec le poids minimum.
 *         Si le graphe est vide, renvoie NULL.
 */
arc *get_arc_min(graph *graphe);

/**
 * @brief Initialise les sommets du graphe à partir d'une liste de noms.
 * @param graphe Le graphe à initialiser.
 * @param listeNomSommets Liste des noms des sommets.
 * @param nbCandidats Nombre de sommets.
 */
void init_sommet(graph *graphe, char *listeNomSommets[], int nbCandidats);

/**
 * @brief Initialise les arcs du graphe à partir d'une matrice duel.
 * @param graphe Le graphe à initialiser.
 * @param mat_duel La matrice duel.
 */
void init_arc(graph *graphe, t_mat_int_dyn *mat_duel);

/**
 * @brief Crée un graphe à partir d'une matrice duel.
 * @param mat_duel La matrice duel.
 * @param listeNomSommets Liste des noms des sommets.
 * @return Un pointeur vers le graphe créé.
 */
graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets);

/**
 * @brief Crée un graphe à partir d'une matrice de caractères.
 * @param mat La matrice de caractères.
 * @return Un pointeur vers le graphe créé.
 */
graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat);

/**
 * @brief Affiche le contenu du graphe (sommets et arcs).
 * @param graphe Le graphe à afficher.
 */
void afficher_graph(graph *graphe);

/**
 * @brief Renvoie l'arc content le poids minimal
 * @param graphe le graphe
 * @return Pointeur vers l'arc
 */
arc *get_arc_min(graph *graphe);

/**
 * @brief Enlève un arc du graphe.
 * @param graphe Graphe duquel enlever l'arc.
 * @param a Arc à enlever.
 * @return Nombre total d'arcs dans le graphe après l'enlèvement.
 */
int enlever_arc(graph *graphe, arc *a);

/**
 * @brief Libère la mémoire allouée pour le graphe.
 * @param graphe Graphe à libérer.
 */
void liberer_graph(graph *graphe);

#endif // GRAPH_H
