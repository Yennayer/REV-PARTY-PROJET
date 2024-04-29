# Projet Avancé
Projet pour l'UE Projet Avancé. Simulation de différents systèmes de vote.

### Membres du groupe
1) **BENAMEUR Yennayer**, 22106001, yennayer.benameur@univ-tlse3.fr 
2) **GUESMI Isra**, 22103741, isra.guesmi@univ-tlse3.fr

# BurgerSupreme
Projet : Procédures de vote pour compiler ce projet .
Pour plus de détails et lus d'informations dans html/index.html  

### Répartition des rôles
1) Fonctions de scrutins: Yennayer & Isra

2) Main, fichiers utils, Makefile: Yennayer & Isra

3) Vérification et anonymisation des votes: Yennayer & Isra

## comment utiliser le programme independant : VERIFY_MY_VOTE :
- Usage : ./verify_my_vote [nom] [Prenom] [code_secret] [fichier_de_vote]
- nom : Nom electeur en majuscule, ex : DUGAT
- prenom : Prenom de l'electeur avec la 1ere lettre en majuscule, ex : Vincent
- code_secret : Code secret de l'electeur
- fichier_de_vote : Fichier de vote csv, ex VoteCondorcet.csv  

## COMMENT UTILISER SCRUTIN :
 Usage : ./scrutin -i [fichier_ballot.csv] -d<option> [fichier_ballot.csv] -o<option> [nom_fichier_log] -m [uni1,uni2,cm,cp,cs,jm,all]
- i nom de fichier csv traite le fichier cité, ex -i VoteCondorcet.csv
- d nom de fichier csv traite le fichier cité, ex -d wiki_paires.csv
- o (option) nom du fichier de log sinon créer automatiquement sous le nom de log.txt, ex -o fichier_log
- m méthode précise la méthode de scrutin à utiliser, ex -m uni1
Remarques : Les deux options -i et -d sont incompatibles mais l’une des deux doit être présente.

Si la balise -o <nom>.txt est donnée, le fichier <nom>.txt sera considéré comme un fichier de log.

Ce fichier (ou à défaut l’écran) recevra les affichages intermédiaires permettant la vérification du vote (le suivi des calculs).
La balise −m suivie d’un nom de méthode ∈ {uni1, uni2, cm, cp, cs, jm, all} permet d’appliquer une méthode de scrutin.
La méthode de Condorcet correspond aux paramètres : {cm, cp, cs}. 
Le paramètre all permet d’appliquer toutes les méthodes valides l’une après l’autre et affiche le résultat de chacune
Si l’option −d est présente, elle désactive l’emploi des argument uni1 et uni2 de l’option −m (Ces méthodes ont besoin des ballots).