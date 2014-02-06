/*
 * partie.h
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#ifndef PARTIE_H_
#define PARTIE_H_

typedef struct partie SPartie;

/**
 * @brief Initialise la partie en fonction des reponses aux differentes questions :
 * noms et natures des joueurs, taille du plateau parmi 9x9, 13x13 et 19x19, etc.
 * Pour rendre cette partie independante du mode texte ou mode SDL,
 * une fonction specifique permettra de prendre en compte ces deux mode.
 * La declaration de cette fonctiontant la suivante : typedef void (*FonctionQuestions)(int numeroQuestion, Partie* partie) ;
*/
// TODO : definir le parametre
SPartie initialisationPartie(/*FonctionQuestions fonctionQuestions*/);

/**
 * @brief Sauvegarde la partie dans sa position actuelle
 * Si la sauvegarde se passe sans probleme la fonction retourne 1, sinon 0
 * */
// TODO :
int partie_sauvegarde(SPartie partie, FILE* fichier);

/**
 * @brief Charge une partie precedement sauvegarde Si le chargement n'est pas possible, retourne un Pointeur NULL
 */
// TODO :
SPartie partie_charge(FILE* fichier);


#endif /* PARTIE_H_ */
