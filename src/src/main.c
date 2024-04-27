#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "jugementMajoritaire.h"
#include "lecture_csv.h"
#include "global.h"
#include "matrice.h"
#include "uninominales.h"
#include "graph.h"
#include "condorcet.h"
#include "condorcet_paires.h"

void erreur(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
// Définition des options longues
    static struct option long_options[] = {
        {"input", required_argument, NULL, 'i'},
        {"duels", required_argument, NULL, 'd'},
        {"log", required_argument, NULL, 'o'},
        {"method", required_argument, NULL, 'm'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    } ;
int main(int argc, char *argv[]) {
    // Variables pour stocker les états des options
    char *inputFileName = NULL;
    char *logFileName = NULL;
    char *method = NULL;
    int option;
    FILE *logfp = stdout; // Par défaut, sortie sur stdout
    t_mat_char_star_dyn *matrice = NULL;
    

    // Analyse des options
    while ((option = getopt_long(argc, argv, "i:d:o:m:h", long_options, NULL)) != -1) {
        switch (option) {
            case 'i':
                inputFileName = optarg;
                // Création et lecture du fichier CSV
                matrice = creer_matrice_char();
                lireFichierCSV(inputFileName, matrice);
                break;
            case 'd':
                // Traitement spécifique pour la matrice de duels
                inputFileName = optarg;
                // Création et lecture du fichier CSV
                matrice = creer_matrice_char();
                lireFichierCSV(inputFileName, matrice);
                break;
            case 'o':
                logFileName = optarg;
                logfp = fopen(logFileName, "w");
                if (logfp == NULL) {
                    erreur("Impossible d'ouvrir le fichier de log.\n");
                }
                break;
            case 'm':
                method = optarg;
                break;
            case 'h':
                // Afficher l'aide ici
                break;
            default:
                erreur("Usage: ./programme -i [inputfile] -o [logfile] -m [method]\n");
        }
    }

    // Vérification des options requises
    if (!inputFileName || (!strcmp(method, "uni1") && !strcmp(method, "uni2") && inputFileName[0] == 'd')) {
        erreur("Options -i (ou -d) et -m sont requises.\n");
    }


    // Traitement selon la méthode de scrutin
    if (strcmp(method, "uni1") == 0) {
       

        int sommeColonnes[MAX_COLUMNS - 4];

        calculerSommecolonnes(matrice, sommeColonnes); // Passer 'mat' directement

        for (int i = 0; i < matrice->nbCols - 4; i++) {
            printf("Somme colonne %d: %d\n", i + 5, sommeColonnes[i]);
    }

        int max = trouverColonneMax(matrice);
        printf("%d\n", max);
        afficher_vainqueur(matrice);
        printf("\n");
    

    } else if (strcmp(method, "uni2") == 0) {
        int sommeColonnes[MAX_COLUMNS - 4];

        calculerSommecolonnes(matrice, sommeColonnes); // Passer 'mat' directement

        for (int i = 0; i < matrice->nbCols - 4; i++) {
            printf("Somme colonne %d: %d\n", i + 5, sommeColonnes[i]);
        }

    int max = trouverColonneMax(matrice);
    printf("%d\n", max);
    afficher_vainqueur(matrice);
    printf("\n");
    afficherResultatsDeuxTours(matrice);
    
    } else if (strcmp(method, "cm") == 0) {
    
    	condorcet(inputFileName);
    	    
    
    } else if (strcmp(method, "cp") == 0) {
    
    	condorcet(inputFileName);
    	
    } else if (strcmp(method, "cs") == 0) {
    
    	condorcet(inputFileName);	    
    } else if (strcmp(method, "jm") == 0) {
    
    	voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    	nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));
	char* fichierBallots = "jugement.csv";
    	lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);
    	printf("Gagnant trouvé avec la méthode du jugement Majoritaire :\n");
    	jugementMajoritaire(v_elect, nb_elect->nb_electeur, NB_CANDIDAT, logfp);
    	free(v_elect);
    	free(nb_elect);    	
    
    
    }if (logfp != stdout) {
        fclose(logfp);
    }

    return 0;
}


