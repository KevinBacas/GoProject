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

// Struct de config
struct {
  char* folderName;
  char* baseName;
} config;

void configMatrice(char* folderName, char* baseName)
{
  config.folderName = folderName;
  config.baseName = baseName;
}

Matrice allouerMatrice(int nbLig, int nbCol)
{
  Matrice matrice;
  matrice.nbLigne = nbLig;
  matrice.nbColonne = nbCol;

  matrice.donnees = malloc(sizeof(char*) * matrice.nbLigne);
  int i,j;
  for( i = 0 ; i < matrice.nbLigne ; ++i)
  {
    matrice.donnees[i] = malloc(sizeof(char) * matrice.nbColonne);
    for( j = 0 ; j < matrice.nbColonne ; ++j)
    {
    	matrice.donnees[i][j] = '.';
    }
  }

  return matrice;
}

Matrice chargerMatrice(char* fichier)
{
  // On init une matrice pour le résultat
  // la fonction renvoi une matrice avec {0,0,NULL} si la lecture s'est mal passée
  Matrice res;
  res.nbLigne = 0;
  res.nbColonne = 0;
  res.donnees = NULL;

  int nbLig = 0;
  int nbCol = 0;
  char** donnees = NULL;

  FILE* ptr_fichier = fopen(fichier, "r");
  if(ptr_fichier)
  {
    int taille_lecture = 256;
    char file_donnees[taille_lecture];

    if(fgets(file_donnees, taille_lecture, ptr_fichier))
    {
      int taille_int = 0;
      while(file_donnees[taille_int] >= '0' && file_donnees[taille_int] <= '9')
      {
        taille_int++;
      }

      if(taille_int > 0)
      {
        char value[taille_int+1];
        int i;
        for(i = 0 ; i < taille_int ; ++i)
        {
          value[i] = file_donnees[i];
        }
        value[i] = '\0';
        nbLig = atoi(value);
      }

      taille_int++;
      int breakpoint = taille_int;

      while(file_donnees[taille_int] >= '0' && file_donnees[taille_int] <= '9')
      {
        taille_int++;
      }

      if(taille_int > breakpoint)
      {
        char value[taille_int-breakpoint+1];
        int i;
        for(i = breakpoint ; i < taille_int ; ++i)
        {
          value[i-breakpoint] = file_donnees[i];
        }
        value[i] = '\0';
        nbCol = atoi(value);
      }
    }

    // initialisation du tableau de données
    res = allouerMatrice(nbLig, nbCol);
    donnees = res.donnees;

    int i,j;
    int isOk = 1;
    for(i = 0 ; i < nbLig && isOk ; ++i)
    {
      isOk = fgets(file_donnees, taille_lecture, ptr_fichier) ? 1 : 0;
      for(j = 0 ; j < nbCol && isOk ; ++j)
      {
        char val = file_donnees[2*j];
        if(val != '\0')
        {
          donnees[i][j] = val;
        }
        else
        {
          isOk = 0;
        }
      }
    }

    if(!isOk)
    {
      res.nbLigne = 0;
      res.nbColonne = 0;
      desallouerMatrice(res);
    }
  }
  return res;
}

void afficherMatrice(Matrice matrice)
{
  printf("%d %d\n", matrice.nbLigne, matrice.nbColonne);
  if(matrice.donnees)
  {
    int i,j;
    for(i = 0 ; i < matrice.nbLigne ; ++i)
    {
      for(j = 0 ; j < matrice.nbColonne ; ++j)
      {
       printf("%c ", matrice.donnees[i][j]);
      }
      printf("\n");
    }
  }
}

void sauvegarderMatrice(Matrice matrice, char* nom_fichier)
{
  FILE* fichier = NULL;

  fichier = fopen(nom_fichier, "w");

  if (fichier != NULL)
  {
    // ecriture des deux premier entiers.
    char int_buffer[10];
    sprintf(int_buffer, "%d", matrice.nbLigne);
    fputs(int_buffer, fichier);
    fputc(' ', fichier);
    sprintf(int_buffer, "%d", matrice.nbColonne);
    fputs(int_buffer, fichier);
    fputc('\n', fichier);
    
    if(matrice.donnees)
    {
      int i;
      for(i = 0 ; i < matrice.nbLigne ; ++i)
      {
       fputs(matrice.donnees[i], fichier);
       fputc('\n', fichier);
      }
    }
    fclose(fichier);
  }
}

int supprimerMatrice(char* nomFichier)
{
  return remove(nomFichier); 
}

void desallouerMatrice(Matrice matrice)
{
  int i;
  for( i = 0 ; i < matrice.nbLigne ; ++i)
  {
    free(matrice.donnees[i]);
  }
  free(matrice.donnees);
}

char getValeurMatrice(Matrice matrice, int x, int y)
{
  return matrice.donnees[x][y];
}

void setValeurMatrice(Matrice matrice, int x, int y, char valeur)
{
  matrice.donnees[x][y] = valeur;
}
