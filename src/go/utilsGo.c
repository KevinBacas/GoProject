#include <stdlib.h>
#include <stdio.h>
#include "utilsGo.h"



SLibertes determineLiberte(SPlateau plateau,SChaine chaine)

STerritoire determineTerritoire(SPlateau plateau, SPosition pos)

int estUnSeki(STerritoire leTerritoire, SChaines lesChaines, SPlateau plateau)

SPositions lesYeuxDeLaChaine(SChaine chaine, SPlateau plateau)

SChaine plateau_determiner_chaine(SPlateau plateau,SPosition pos)

void plateau_realiser_capture(SPlateau plateau, SChaine chaine)

int plateau_est_identique(SPlateau plateau, SPlateau ancienPlateau)

int plateau_copie(SPlateau from, SPlateau to)

SChaines plateau_entoure_un_territoire(STerritoire leTerritoire, SPlateau plateau)
