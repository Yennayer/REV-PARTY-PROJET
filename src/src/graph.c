#include <stdlib.h>

#include "matrice.h"
#include "graph.h"
#include "global.h"

/**
 * \brief Crée un nouveau sommet avec un nom spécifié.
 * \param nom Nom du nouveau sommet.
 * \return Pointeur vers le sommet créé.
 */
sommet *creer_sommet(char *nom) {
    sommet *s = malloc(sizeof(sommet));
    s->nom = nom;
    s->nbPredecesseur = 0;
    s->nbSuccesseur = 0;
    return s;
}
/**
 * \brief Crée un nouvel arc entre deux sommets avec un poids spécifié.
 * \param arrivee Pointeur vers le sommet d'arrivée.
 * \param depart Pointeur vers le sommet de départ.
 * \param poids Poids de l'arc.
 * \return Pointeur vers l'arc créé.
 */
arc *creer_arc(sommet *arrivee, sommet *depart, int poids) {
    arc *a = malloc(sizeof(arc));
    a->arrivee = arrivee;
    a->depart = depart;
    a->poids = poids;
    return a;
}

/**
 * \brief Crée un nouveau graphe vide.
 * \return Pointeur vers le graphe créé.
 */
 
graph *creer_graph() {
    graph *graphe = malloc(sizeof(graph));
    graphe->sommets = NULL;
    graphe->nbSommet = 0;
    graphe->arcs = NULL;
    graphe->nbArc = 0;
    return graphe;
}
/**
 * \brief Ajoute un sommet à un graphe.
 * \param graphe Pointeur vers le graphe.
 * \param somm Pointeur vers le sommet à ajouter.
 * \return Nouveau nombre de sommets dans le graphe.
 */
 
int add_sommet(graph *graphe, sommet *somm) {
    int nbs = (++(graphe->nbSommet));
    graphe->sommets = realloc(graphe->sommets, nbs * sizeof(sommet *));
    graphe->sommets[nbs - 1] = somm;
    return nbs;
}

/**
 * \brief Ajoute un arc à un graphe.
 * \param graphe Pointeur vers le graphe.
 * \param a Pointeur vers l'arc à ajouter.
 * \return Nouveau nombre d'arcs dans le graphe.
 */
 
int add_arc(graph *graphe, arc *a) {
    int nbArc = (++(graphe->nbArc));
    graphe->arcs = realloc(graphe->arcs, nbArc * sizeof(arc *));
    graphe->arcs[nbArc - 1] = a;
    (a->arrivee)->nbPredecesseur++;
    (a->depart)->nbSuccesseur++;
    return nbArc;
}

/**
 * \brief Récupère l'arc avec le poids minimum dans un graphe.
 * \param graphe Pointeur vers le graphe.
 * \return Pointeur vers l'arc avec le poids minimum, NULL si aucun arc.
 */
 
arc *get_arc_min(graph *graphe) {
    if (graphe->nbArc == 0) {
        return NULL;
    }
    arc *min = graphe->arcs[0];
    for (int i = 1; i < graphe->nbArc; i++) {
        if (graphe->arcs[i]->poids < min->poids) {
            min = graphe->arcs[i];
        }
    }
    return min;
}

/**
 * \brief Initialise les sommets d'un graphe à partir d'une liste de noms.
 * \param graphe Pointeur vers le graphe.
 * \param listeNomSommets Tableau de chaînes contenant les noms des sommets.
 * \param nbCandidats Nombre de sommets à initialiser.
 */

void init_sommet(graph *graphe, char *listeNomSommets[], int nbCandidats) {
    sommet *pSommet;
    for (int i = 0; i < nbCandidats; i++) {
        pSommet = creer_sommet(listeNomSommets[i]);
        add_sommet(graphe, pSommet);
    }
}
/**
 * \brief Initialise les arcs d'un graphe à partir d'une matrice de duels.
 * \param graphe Pointeur vers le graphe.
 * \param mat_duel Pointeur vers la matrice de duels.
 */

void init_arc(graph *graphe, t_mat_int_dyn *mat_duel) {
    int colonne = mat_duel->nbCol;
    int poids, poids2;
    sommet *arrivee, *depart;
    arc *pArc;
    for (int i = 0; i < colonne - 1; i++) {
        for (int j = i + 1; j < colonne; j++) {
            poids = mat_duel->tab[i][j];
            poids2 = mat_duel->tab[j][i];
            arrivee = graphe->sommets[j];
            depart = graphe->sommets[i];
            if (poids < poids2) {
                poids = poids2 - poids;
                arrivee = graphe->sommets[i];
                depart = graphe->sommets[j];
            } else {
                poids = poids - poids2;
            }
            pArc = creer_arc(arrivee, depart, poids);
            add_arc(graphe, pArc);
        }
    }
}

/**
 * \brief Crée un graphe à partir d'une matrice de duels et d'une liste de noms de sommets.
 * \param mat_duel Pointeur vers la matrice de duels.
 * \param listeNomSommets Tableau de chaînes contenant les noms des sommets.
 * \return Pointeur vers le graphe créé.
 */
 
graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets) {
    int nbCandidats = mat_duel->nbCol;
    graph *graphe = creer_graph();
    init_sommet(graphe, listeNomSommets, nbCandidats);
    init_arc(graphe, mat_duel);
    return graphe;
}
/**
 * \brief Crée un graphe à partir d'une matrice de chaînes de caractères.
 * \param mat Pointeur vers la matrice de chaînes de caractères.
 * \return Pointeur vers le graphe créé.
 */

graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat) {
    graph *graphe;
    char **entete = get_candidats(mat);
    t_mat_int_dyn *mat_duel = construire_mat_duel(mat);
    graphe = creer_graphe_de_matrice_duel(mat_duel, entete);
    supprimer_matrice_int(mat_duel);
    return graphe;
}
/**
 * \brief Affiche un graphe.
 * \param graphe Pointeur vers le graphe à afficher.
 */

void afficher_graph(graph *graphe) {
    if (graphe == NULL) {
        printf("Le pointeur vers le graphe est nul.\n");
        return;
    }
    printf("Affichage Graphe :\n\n[Sommets]\n");
    // Vérification d'indices avant d'accéder aux tableaux
    for (int i = 0; i < graphe->nbSommet; i++) {
        if (graphe->sommets[i] != NULL) {
            printf("%s \n", graphe->sommets[i]->nom);
        }
    }
    printf("\n[Arcs]\n");
    // Vérification d'indices avant d'accéder aux arcs
    for (int j = 0; j < graphe->nbArc; j++) {
        if (graphe->arcs[j] != NULL && graphe->arcs[j]->depart != NULL && graphe->arcs[j]->arrivee != NULL) {
            printf("(%s) ---%d---> (%s)\n", graphe->arcs[j]->depart->nom, graphe->arcs[j]->poids, graphe->arcs[j]->arrivee->nom);
        }
    }
}

/**
 * \brief Enlève un arc d'un graphe.
 * \param graphe Pointeur vers le graphe.
 * \param a Pointeur vers l'arc à enlever.
 * \return Nouveau nombre d'arcs dans le graphe.
 */

int enlever_arc(graph *graphe, arc *a) {
    int nbArc = (graphe->nbArc) - 1;
    arc **nouvelListe = NULL;
    int temp = 0;
    if (nbArc > 0) {
        nouvelListe = (arc **)malloc(nbArc * sizeof(arc *));
        for (int i = 0; i < (graphe->nbArc); i++) {
            if ((graphe->arcs[i]) != a) {
                nouvelListe[temp] = (graphe->arcs[i]);
                temp += 1;
            } else {
                free((graphe->arcs[i]));
            }
        }
    }
    free(graphe->arcs);
    graphe->arcs = nouvelListe;
    (graphe->nbArc)--;
    return nbArc;
}

/**
 * \brief Libère la mémoire allouée à un graphe.
 * \param graphe Pointeur vers le graphe à libérer.
 */

void free_graph(graph *graphe) {
    for (int i = 0; i < (graphe->nbSommet); i++) {
        free((graphe->sommets)[i]);
    }
    for (int i = 0; i < (graphe->nbArc); i++)
    {
        free((graphe->arcs)[i]);
    }
    free(graphe->arcs);
    free(graphe->sommets);
    free(graphe);
}
