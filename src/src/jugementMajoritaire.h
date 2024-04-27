#ifndef JUGEMENT_MAJORITAIRE_H
#define JUGEMENT_MAJORITAIRE_H

#include "global.h"
#include <stdio.h>
/**
 * \fn float* appreciationCandidat(voteElecteur **votes, int numCandidat, int nbVotants, FILE *fptr)
 * \brief Calcule l'appréciation pour un candidat donné.
 * \param[in] votes Tableau de pointeurs vers les votes des électeurs.
 * \param[in] numCandidat Index du candidat.
 * \param[in] nbVotants Nombre total de votants.
 * \param[in,out] fptr Pointeur vers le fichier de log.
 * \return Un tableau contenant l'indice de l'appréciation la plus élevée et le score correspondant.
 */
void jugementMajoritaire(voteElecteur **votes,int nbVotants,int nbCandidat,const char* fichierLog);
/**
 * \fn void jugementMajoritaire(voteElecteur **votes, int nbVotants, int nbCandidat, const char *fichierLog)
 * \brief Effectue le jugement majoritaire pour déterminer le candidat gagnant.
 * \param[in] votes Tableau de pointeurs vers les votes des électeurs.
 * \param[in] nbVotants Nombre total de votants.
 * \param[in] nbCandidat Nombre total de candidats.
 * \param[in] fichierLog Nom du fichier de log pour enregistrer les résultats.
 */
float *appreciationCandidat(voteElecteur **votes,int numCandidat,int nbVotants,FILE *fptr);


#endif
