#include<stdio.h>

#define SIZE 10000

typedef struct
{
  char nume[35];
  int varsta;
  float nota;
}Student_t;

FILE *deschidereFisier(char *fis,char *pt);
void citire(FILE *fin,Student_t v[SIZE],int *n);
void scriereFisierBinar(FILE *fout,Student_t v[SIZE],int n);
void cautare(FILE *fin,int indx);
void afisare(Student_t v[SIZE],int n);
void scriereFisierText(FILE *fout,Student_t v[SIZE],int n);
