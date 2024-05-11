#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Bin.h"


typedef Student_t TipNod_t;
typedef struct Arbore* Node_t;

typedef struct Arbore
{
  int cheie;
  TipNod_t info;
  Node_t st;
  Node_t dr;
}Arbore_t;

Node_t creare(TipNod_t v[SIZE],int n);
void modificare(Node_t radacina,TipNod_t info,int cheie);
int cautareNod(Node_t radacina,TipNod_t info);
Node_t stergere(Node_t radacina,int cheie);
void preordine(Node_t radacina);
void postordine(Node_t radacina);
void inordine(Node_t radacina);
void eliberare(Node_t radacina);

