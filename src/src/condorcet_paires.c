/**
 * \file condorcet_paires.c
 * \brief Implémentation de la méthode Condorcet paires pour des élections.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "condorcet_paires.h"
#include "utils_sd.h"
#include "condorcet.h"

#include "graph.h"

/**
 * \fn bool findCycle(t_arc_p *debutarc, t_arc_p *vers, int taille_debutarc, int taille_vers, t_arc_p arcCourant)
 * \brief Détecte la présence d'un cycle dans un graphe dirigé.
 * \param[in] debutarc Tableau d'arcs représentant le début du parcours.
 * \param[in] vers Tableau d'arcs représentant la fin du parcours.
 * \param[in] taille_debutarc Taille du tableau debutarc.
 * \param[in] taille_vers Taille du tableau vers.
 * \param[in] arcCourant L'arc actuellement examiné.
 * \return Vrai (true) s'il y a un cycle, faux (false) sinon.
 * \details Cette fonction vérifie la présence d'un cycle dans un graphe en parcourant deux tableaux d'arcs. 
 *          Elle est utilisée pour identifier des cycles dans le cadre de l'application de la méthode Condorcet par paires.
 */

bool findCycle(t_arc_p *debutarc, t_arc_p *vers, int taille_debutarc, int taille_vers, t_arc_p arcCourant){
    if(taille_debutarc < taille_vers){
        for(int i = 0; i<taille_debutarc; i++){
            if(debutarc[i].orig != arcCourant.orig){
                for(int j = 0; j<taille_vers; j++){
                    if(debutarc[i].orig == vers[j].dest) return true;  //il y a un cycle
                }
            }
            if(debutarc[i].dest != arcCourant.orig){
                for(int j = 0; j<taille_vers; j++){
                    if(debutarc[i].dest == vers[j].orig) return true;  //il y a un cycle
                }
            }
        }
    }else{
        for(int i = 0; i<taille_vers; i++){
            if(vers[i].orig != arcCourant.dest){
                for(int j = 0; j<taille_debutarc; j++){
                    if(vers[i].orig == debutarc[j].dest) return true;  //il y a un cycle
                }
            }
            if(vers[i].dest != arcCourant.dest){
                for(int j = 0; j<taille_debutarc; j++){
                    if(vers[i].dest == debutarc[j].orig) return true;  //il y a un cycle
                }
            }
        }
    }
    return false;
}


/**
 * \fn void eliminationCycle(t_arc_p *tarc, t_arc_p *tarc_reduit, int *compteur, int taille_tarc)
 * \brief Élimine les cycles dans un graphe de duels pour créer un graphe acyclique.
 * \param[in] tarc Tableau des arcs initiaux du graphe.
 * \param[out] tarc_reduit Tableau des arcs du graphe après élimination des cycles.
 * \param[out] compteur Pointeur vers le compteur des arcs dans le graphe réduit.
 * \param[in] taille_tarc Taille du tableau des arcs initiaux.
 * \details Cette fonction parcourt les arcs du graphe et élimine ceux qui créent des cycles, 
 *          permettant la création d'un graphe acyclique représentatif des duels entre candidats.
 */
void eliminationCycle(t_arc_p *tarc, t_arc_p *tarc_reduit, int *compteur, int taille_tarc){

    tarc_reduit[0] = tarc[0];
    tarc_reduit[1] = tarc[1];
    int c = 2;
    for(int i = 2; i<taille_tarc; i++){
        t_arc_p arcCourant = tarc[i];
        t_arc_p de[c];
        t_arc_p vers[c];
        int indiceDe = 0;
        int indiceVers = 0;
        for(int j = 0; j<c; j++){
            if(arcCourant.orig == tarc_reduit[j].orig || arcCourant.orig == tarc_reduit[j].dest){
                de[indiceDe] = tarc_reduit[j];
                indiceDe++;
            }
            if(arcCourant.dest == tarc_reduit[j].orig || arcCourant.dest == tarc_reduit[j].dest){
                vers[indiceVers] = tarc_reduit[j];
                indiceVers++;
            }
        }
        if(indiceDe == 0 || indiceVers == 0){
            tarc_reduit[c] = arcCourant;
            c++;
        }
        if(indiceDe != 0 && indiceVers != 0){
            if(findCycle(de, vers, indiceDe, indiceVers,arcCourant) == false){
                tarc_reduit[c] = arcCourant;
                c++;
            }
        }
    }
    *compteur = c;
}
/**
 * \fn int condorcet_paires(t_mat_int_dyn *matrice_duels, FILE* log)
 * \brief Trouve le vainqueur Condorcet en utilisant une méthode basée sur le tri des paires de duels.
 * \param[in] matrice_duels Pointeur vers une matrice dynamique représentant les duels entre candidats.
 * \param[in,out] log Pointeur vers un fichier pour enregistrer les opérations et les résultats.
 * \return L'indice du candidat vainqueur selon la méthode Condorcet.
 * \details Cette fonction procède en plusieurs étapes :
 *          1. Copie et transforme la matrice des duels en une matrice de différences.
 *          2. Crée un tableau de structures représentant les arcs entre les candidats.
 *          3. Trie ce tableau par ordre décroissant des poids (différences de votes).
 *          4. Élimine les cycles du graphe formé par ces arcs pour obtenir un graphe acyclique.
 *          5. Détermine le vainqueur Condorcet à partir du graphe acyclique.
 */

int condorcet_paires(t_mat_int_dyn *matrice_duels, FILE* log){
    int nbColonne = matrice_duels->nbCol;
    int nbLigne = matrice_duels->nbRows;

    int matrice_copy[nbColonne][nbLigne];
    for(int i = 0; i<nbLigne; i++){
        for(int j=0; j<nbColonne;j++){
            matrice_copy[i][j] = 0;
        }
    }

    int val1 = 0; 
    int val2 = 0;
    for(int i = 0; i<nbLigne; i++){
        for(int j = i+1; j<nbColonne; j++){
            val1 = matrice_duels->tab[i][j];
            val2 = matrice_duels->tab[j][i];
            if(val1 > val2) matrice_copy[i][j] += abs(val1 - val2);
            else matrice_copy[j][i] += abs(val1 - val2); 
        }
    }

    fprintf(log,"\nMatrice qui contient les duels gagnant:\n");
    for(int i=0;i<nbLigne;i++){
        for(int j=0;j<nbColonne;j++)
            fprintf(log,"%d ",matrice_copy[i][j]);
        fprintf(log,"\n");
    }
    fprintf(log,"\n");

    t_arc_p tarc[nbColonne*2]; 
    int indiceTarc = 0;
    for(int de = 0; de<nbLigne; de++){
        for(int vers = 0; vers<nbColonne; vers++){
            if(matrice_copy[de][vers] != 0){
                tarc[indiceTarc].orig = de;
                tarc[indiceTarc].dest = vers;
                tarc[indiceTarc].poids = matrice_copy[de][vers];
                indiceTarc++;
            }
        }
    }


    int taille_tarc = nbColonne*2;
    int a, b, c;
    for (int i = 0; i < taille_tarc - 1; i++) {
        for (int j = 0; j < taille_tarc - 1 - i; j++) {

            if (tarc[j].poids < tarc[j + 1].poids) {
                a = tarc[j].orig;
                b = tarc[j].dest;
                c = tarc[j].poids;
                tarc[j].poids = tarc[j + 1].poids;
                tarc[j].orig = tarc[j+1].orig;
                tarc[j].dest = tarc[j+1].dest;
                tarc[j+1].poids = c;
                tarc[j+1].orig = a;
                tarc[j+1].dest = b;
            }
        }
    }
    

    fprintf(log,"\nListe duels gagnants par ordre décroissant\n");
    for(int i =0; i<nbColonne*2; i++){
        fprintf(log,"%d ", tarc[i].poids);
    }
    fprintf(log,"\n");

    t_arc_p tarc_reduit[taille_tarc];
    int compteur = 0;
    eliminationCycle(tarc, tarc_reduit, &compteur, taille_tarc);
    //affichage liste reduite
    fprintf(log,"\nListe des votes représentant le graphe sans cycle:\n");
    for(int i=0; i<compteur; i++){
        fprintf(log,"%d ", tarc_reduit[i].poids);
    }
    fprintf(log,"\n");
    // on a le tableau représentant le graphe des duels sans cycles
    // on peut alors trouver le vainqueur de Condorcet
    int recherche_win[nbColonne];
    for(int i = 0; i<nbColonne; i++){
        recherche_win[i] = 0;
    }
    for(int candidat = 0; candidat<nbColonne; candidat++){
        for(int c = 0; c<compteur; c++){
            if(tarc_reduit[c].dest == candidat) {
                recherche_win[candidat]+=1;
            }  
        }
    }
    fprintf(log,"\nListe du nombre d'arcs entrant pour chaque candidats\n");
    for(int i = 0; i<nbColonne; i++){
        fprintf(log,"%d ", recherche_win[i]);
    }
    fprintf(log,"\n");
    //parcours de recherche_win pour trouver le min
    //le min est le vainqueur de Condorcet avec rangement des paires par ordre décroissant
    int winner = recherche_win[0];
    int ind_win = 0;
    for(int i = 1; i<nbColonne; i++){
        if(recherche_win[i]< winner) {
            winner = recherche_win[i];
            ind_win = i;
        }
    }
    return ind_win;
}


/**
 * \fn void liberer_memoire_s3(t_mat_int_dyn *mat)
 * \brief Libère la mémoire allouée à une matrice dynamique.
 * \param[in,out] mat Pointeur vers la matrice dynamique à libérer.
 */
void liberer_memoire_s3(t_mat_int_dyn *  mat)
{
     for (int i = 0; i < mat->nbCol; ++i) 
     {
        free(mat->tab[i]);
    }  
    free(mat->tab);
}


/**
 * \fn void prog(char *filename, FILE *log, int option)
 * \brief Programme principal pour l'exécution de la méthode Condorcet et Condorcet paires.
 * \param[in] filename Nom du fichier CSV contenant les bulletins de vote ou les duels.
 * \param[in,out] log Fichier pour la journalisation des résultats.
 * \param[in] option Option de traitement pour la matrice des duels.
 * \details Cette fonction gère la lecture des données, le traitement selon la méthode Condorcet
 */
 
 
void prog(char*filename, FILE* log, int option){
    Resultats *result=construction_mat_duels(option , filename, log);
    afficherMatricee(result->duels_mat, log);
    int resultat = condorcet1(result->duels_mat, log);
    if (resultat != -1) {
        fprintf(log,"Le vainqueur de Condorcet est le candidat %s.\n\n", result->nom_candidats[resultat]);
        fprintf(log,"Mode de scrutin : Condorcet Pair, %d candidats, %d votants, vainqueur = %s\n\n ",result->duels_mat->nbCol,result->nb_votant,result->nom_candidats[resultat]);
        //fprintf(log,"Un seul gagnant de Condorcet a été trouvé.\nLe gagnant est le candidat:%s\n",result->nom_candidats[resultat]);
    } else  {
        int Gpairs = condorcet_paires(result->duels_mat, log);
        afficher_vainqueur("Condorcet Paires", result->duels_mat->nbCol, result->duels_mat->nbRows, result->nom_candidats[Gpairs], 0, 0, log);
    }
    liberer_memoire_s3(result->duels_mat);
}
