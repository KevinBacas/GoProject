/*
 * fonction.h
 *
 *  Created on: 2 févr. 2014
 *      Author: Jacky
 */

#ifndef FONCTION_H_
#define FONCTION_H_

int compter_contact(SPlateau* plateau,SPion* pion, ECouleur couleur);

int compter_liberte(SPlateau* plateau, listePion* chaine);

void capture_chaine(SPlateau* plateau, listePion* pion);

#endif /* FONCTION_H_ */
