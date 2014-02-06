#ifndef __ENSEMBLE_COLORE_H__
#define __ENSEMBLE_COLORE_H__

#include "ensemblePosition.h"
#include "couleur.h"

typedef struct ensembleColore SEnsembleColore;

SEnsembleColore* creerEnsembleColore();

void detruireEnsembleColore(SEnsembleColore* e_colore);

ECouleur couleurEnsembleColore(SEnsembleColore* e_colore);

SEnsemblePosition* listEnsembleColore(SEnsembleColore* e_colore);

#endif // __ENSEMBLE_COLORE_H__
