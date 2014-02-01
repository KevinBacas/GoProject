#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"

int main()
{
  int lig = 10;
  int col = 7;

  Matrice matrice = allouerMatrice(lig, col);
  int i,j;
  char c = '0';
  for( i = 0 ; i < lig ; ++i)
  {
    for( j = 0 ; j < col ; ++j)
    {
      setValeurMatrice(matrice, i, j, c);
      ++c;
    }
  }

  return EXIT_SUCCESS;
}
