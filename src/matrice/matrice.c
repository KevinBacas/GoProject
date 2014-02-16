/**
  * @author : Bacas Kévin & Louis Delbosc
  * @version : 1.0
  * @file : matrice.c
  */

#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

struct matrice{
	char **donnees;
	int nbLigne;
	int nbColonne;
};

Matrice* allouerMatrice(int nbLig, int nbCol)
{
  Matrice* matrice = malloc(sizeof(Matrice));
  matrice->nbLigne = nbLig;
  matrice->nbColonne = nbCol;

  matrice->donnees = malloc(sizeof(char*) * matrice->nbLigne);
  int i,j;
  for( i = 0 ; i < matrice->nbLigne ; ++i)
  {
    matrice->donnees[i] = malloc(sizeof(char) * matrice->nbColonne);
    for( j = 0 ; j < matrice->nbColonne ; ++j)
    {
    	matrice->donnees[i][j] = '.';
    }
  }

  return matrice;
}

Matrice* chargerMatrice(FILE* fichier)
{
  // On init une matrice pour le résultat
  // la fonction renvoi une matrice avec {0,0,NULL} si la lecture s'est mal passée
  Matrice* res = NULL;

  int nbLig = 0;
  int nbCol = 0;

  if(fichier)
  {
	  fscanf(fichier, "%d %d\n", &nbLig, &nbCol);
	  res = allouerMatrice(nbLig, nbCol);
	  if(res->donnees)
	  {
		  int i,j;
		  for(i = 0 ; i < res->nbLigne ; ++i)
		  {
			  for(j = 0 ; j < res->nbColonne ; ++j)
			  {
				  fscanf(fichier, "%c ", &(res->donnees[i][j]));

			  }
		  }
	  }
  }

  return res;
}

void afficherMatrice(Matrice* matrice)
{
  printf("%d %d\n", matrice->nbLigne, matrice->nbColonne);
  if(matrice->donnees)
  {
    int i,j;
    for(i = 0 ; i < matrice->nbLigne ; ++i)
    {
      for(j = 0 ; j < matrice->nbColonne ; ++j)
      {
       printf("%c ", matrice->donnees[i][j]);
      }
      printf("\n");
    }
  }
}

void sauvegarderMatrice(Matrice* matrice, FILE* fichier)
{
	if(fichier && matrice)
	{
		fprintf(fichier, "%d %d\n", matrice->nbLigne, matrice->nbColonne);
		if(matrice->donnees)
		{
			int i,j;
		    for(i = 0 ; i < matrice->nbLigne ; ++i)
		    {
		        for(j = 0 ; j < matrice->nbColonne ; ++j)
		        {
		        	fprintf(fichier, "%c ", matrice->donnees[i][j]);
		        }
		        fprintf(fichier, "\n");
		    }
		}
	}
}

int supprimerMatrice(char* nom_fichier)
{
  return remove(nom_fichier);
}

void desallouerMatrice(Matrice* matrice)
{
  int i;
  for( i = 0 ; i < matrice->nbLigne ; ++i)
  {
    free(matrice->donnees[i]);
  }
  free(matrice->donnees);
  free(matrice);
}

char getValeurMatrice(Matrice* matrice, int x, int y)
{
  return matrice->donnees[x][y];
}

void setValeurMatrice(Matrice* matrice, int x, int y, char valeur)
{
	if(x > -1 && x < matrice->nbLigne && y > -1 && y < matrice->nbColonne)
		matrice->donnees[x][y] = valeur;
}

int getNbLigne(Matrice* matrice)
{
	return matrice->nbLigne;
}

int getNbColonne(Matrice* matrice)
{
	return matrice->nbColonne;
}
