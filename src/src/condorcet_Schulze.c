
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils_sd.h"
#include "global.h"
#include "duel.h"
#include "graph.h"
#include "condorcet.c"
#include "lecture_csv.c"
#include "matrice.c"

#include "condorcet_Schulze.h"

/////-- METHODE DE SCHULZE  --////

// recherche et supprime le plus petit élément non nul d'une matrice dynamique d'entiers
void enlever_min(t_mat_int_dyn  *  matpref)
{
    int min=100;
    int id_l;
    int id_c;
    for(int i=0;i<matpref->nbRows;i++)
    {
        for(int k=0;k<matpref->nbCol;k++)
        {
            int nombre=matpref->tab[i][k];
            if(nombre<min && nombre!=0 )
            {
                min=nombre;
                id_l=i;
                id_c=k;
            }
        }
    }
    matpref->tab[id_l][id_c]=0;
}

/// Calcul de la somme des éléments d'une colonne spécifique dans une matrice dynamique d'entiers
int somme_colonnes(t_mat_int_dyn  *  matpref,int p) 
{
    int somme=0;
    for(int i=0;i<matpref->nbRows;i++)
    {
        somme+=matpref->tab[i][p];
    }
 return somme;
}

 ///renvoi true si on a trouver un gagnant
bool gagnant(t_mat_int_dyn  *  matpref,int *res){
    for (int i = 0; i < matpref->nbCol; i++) {
        int j = somme_colonnes(matpref, i);
        if (j == 0) {
            *res = i;
            return true;}
    }
    return false;
}
///Crée et retourne une matrice de préférences à partir d'une matrice de duels
t_mat_int_dyn  * matrice_pref(Resultats *matriceDuels,FILE * log) 
{
    int ligne=matriceDuels->duels_mat->nbRows;
    int colonne=matriceDuels->duels_mat->nbCol;
    int** matpref;
    matpref = (int**)malloc(ligne* sizeof(int*));
    for (int i = 0; i < colonne; ++i) {
        matpref[i] = (int*)malloc(colonne * sizeof(int));
    }         
    for (int i = 0; i < matriceDuels->duels_mat->nbRows; i++) {
        for (int j = 0; j < matriceDuels->duels_mat->nbCol; j++) {
            if (i != j) {
                        int score_1 =matriceDuels->duels_mat->tab[i][j];
                        int score_2 = matriceDuels->duels_mat->tab[j][i];
                        if (score_1 > score_2) {
                            matpref[i][j]=abs(score_1-score_2);
                        } else{
                            matpref[j][i]=abs(score_2-score_1);
                        }
            }
        }
    }
    t_mat_int_dyn * mat_preference=(t_mat_int_dyn* )malloc(sizeof(t_mat_int_dyn));
    mat_preference->tab=matpref;
    mat_preference->nbCol=colonne;
    mat_preference->nbRows=ligne;
    fprintf(log,"\nMatrice des preferences:\n");
    for(int i=0;i<mat_preference->nbCol;i++){
        for(int j=0;j<mat_preference->nbRows;j++)
            fprintf(log,"%2d ",mat_preference->tab[i][j]);
        fprintf(log,"\n");
    }
    return mat_preference;
}
///Libère la mémoire allouée dynamiquement pour une matrice dynamique d'entiers 
void liberer_memoire_s(t_mat_int_dyn *  mat){
    for (int i = 0; i < mat->nbCol; ++i) 
     {
        free(mat->tab[i]);
    }  
    free(mat->tab);
}


void schulze(FILE * log,int option,char *nomFichier)
{
    Resultats *result=construction_mat_duels(option,nomFichier,log);
    t_mat_int_dyn * mat_p= matrice_pref(result,log);
    int resultat = condorcet1(result->duels_mat,log);
    int indice_gagant=0;
    //il y a un gagnant de condorcet
    if (resultat != -1) 
    {
        fprintf(log,"Un seul gagnant de Condorcet a été trouvé.\n le gagnant est le candidat:%s\n",result->nom_candidats[resultat]);
    } 
    else {
        fprintf(log,"Il y a un conflit de Condorcet avec plusieurs gagnants ou aucun gagnant.\n");
        fprintf(log,"Methode de schulze:\n\n");
        bool gagnant_trouver=gagnant(mat_p,&indice_gagant);
        while(!(gagnant_trouver))
        {
            enlever_min(mat_p);
            gagnant_trouver=gagnant(mat_p,&indice_gagant);
        }
    }
    if(indice_gagant>=0 && indice_gagant<result->duels_mat->nbCol )
    {
        afficher_vainqueur("Condorcet Schulze",mat_p->nbCol,result->nb_votant,result->nom_candidats[indice_gagant],0,0,log);
    }
    else
    {
        fprintf(log,"La methode de Schulze n'a pas trouevr de gagant\n");
    }

    liberer_memoire_s(mat_p);
}