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
 * @brief Initialise la partie en fonction des r ́ponses aux diff ́rentes questions :
 * noms et natures des joueurs, taille du plateau parmi 9x9, 13x13 et 19x19, etc.
 * Pour rendre cette partie ind ́pendante du mode texte ou mode SDL,
 * une fonction sp ́cique permettra de prendre en compte ces deux mode.
 * La d ́claration de cette fonction  ́tant la suivante : typedef void (*FonctionQuestions)(int numeroQuestion, Partie* partie) ;
*/
// TODO : définir le paramètre
SPartie initialisationPartie(/*FonctionQuestions fonctionQuestions*/);

/**
 * @brief Sauvegarde la partie dans sa position actuelle
 * Si la sauvegarde se passe sans probl`me la fonction retourne 1, sinon 0
 * */
int partie_sauvegarde(SPartie partie, FILE* fichier);

/**
 * @brief Charge une partie pr ́c ́dement sauvegard ́e. Si le chargement n’est pas possible, retourne un Pointeur NULL
 */
SPartie partie_charge(FILE* fichier);


#endif /* PARTIE_H_ */
