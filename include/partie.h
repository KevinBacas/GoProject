/*
 * partie.h
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <stdio.h>

typedef struct partie SPartie;

typedef void(*FonctionQuestions)(int numeroQuestion, SPartie* partie);

/**
 * @brief fonction de question pour la version terminal.
 */
void questionsTerminal(int i, SPartie* partie);

/**
 * @brief Initialise la partie en fonction des reponses aux differentes questions :
 * natures des joueurs, taille du plateau parmi 9x9, 13x13 et 19x19, Komi.
 * Pour rendre cette partie independante du mode texte ou mode SDL,
 * une fonction specifique permettra de prendre en compte ces deux mode.
 * La declaration de cette fonctiontant la suivante : typedef void (*FonctionQuestions)(int numeroQuestion, Partie* partie) ;
*/
SPartie* initialisationPartie(FonctionQuestions fonctionQuestions);

void detruirePartie(SPartie* partie);

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
//TODO :
void jouer_coup(SPartie partie, SPosition position);

/**
 * @brief Sauvegarde la partie dans sa position actuelle
 * Si la sauvegarde se passe sans probleme la fonction retourne 1, sinon 0
 * */
// TODO :
void partie_sauvegarde(SPartie* partie, FILE* fichier);

void jouerPartie(SPartie* partie);

#endif /* PARTIE_H_ */
