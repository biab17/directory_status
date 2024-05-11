#include<stdio.h>

#define SIZE 10000

typedef struct
{
  char nume[35];
  int varsta;
  float nota;
}Student_t;

void citire(char *fis,Student_t v[SIZE],int *n);
void scriereFisierBinar(char *fis,Student_t v[SIZE],int n);
void cautare(char *fis,int indx);
void afisare(Student_t v[SIZE],int n);
void scriereFisierText(char *fis,Student_t v[SIZE],int n);
