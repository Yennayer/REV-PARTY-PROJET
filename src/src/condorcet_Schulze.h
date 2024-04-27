
#ifndef REV_PARTY_CONDORCET_SCHULZE_H
#define REV_PARTY_CONDORCET_SCHULZE_H
#include "global.h"
#include "liste.h"
#include "elementliste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils_sd.h"
#include "global.h"
#include "duel.h"
#include "graph.h"


/**
 *@fn void schulze(FILE * log,int option,char *nomFichier);
 *@brief Fonction qui effectue le déroulement complet de la méthode de Condorcet schulze
 *@param[in] char *nomFichier -> nom du fichier conteneant les resultats du vote 
 *@param[in] FILE * log -> fichier qui contiendra les logs a la fin de l'exécution du programme et qui permettra a l'utilisateur de vérifier les calculs
*/
void schulze(FILE * log,int option,char *nomFichier);



#endif