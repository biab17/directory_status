#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ArboriBinari.h"

int main()
{
  Student_t v[SIZE];
  int n;
  FILE *fin=deschidereFisier("testare.bin","rb");
  citire(fin,v,&n);
  Node_t radacina = creare(v,n);
  preordine(radacina);
  printf("\n");
  modificare(radacina,v[0],3);
  preordine(radacina);
  printf("\n");
  postordine(radacina);
  printf("\n");
  inordine(radacina);
  printf("\n");
  printf("%d\n",cautareNod(radacina,v[2]));
  radacina=stergere(radacina,2);
  preordine(radacina);
  printf("\n");
  eliberare(radacina);
  preordine(radacina);
  printf("\n");
  fclose(fin);
  return 0;
}
