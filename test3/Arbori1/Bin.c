#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Bin.h"

FILE *deschidereFisier(char *fis,char *pt)
{
  FILE *f=fopen(fis,pt);
  if(fis==NULL)
    {
      printf("Eroare deschidere fisier\n");
      exit(-1);
    }
  return f;
}

void citire(FILE *fin,Student_t v[SIZE],int *n)
{
  int i=0;
  while(1)
    {
      if(fread(&v[i],sizeof(Student_t),1,fin)!=1)
	break;
      i++;
    }
  (*n)= i;
}

void afisare(Student_t v[SIZE],int n)
{
  for(int i=0;i<n;i++)
    {
      printf("%s %d %f\n",v[i].nume,v[i].varsta,v[i].nota);
    }
}

void scriereFisierBinar(FILE *fout,Student_t v[SIZE],int n)
{
  fwrite(v,sizeof(Student_t),n,fout);
}


void cautare(FILE *fin,int indx)
{
  fseek(fin,indx * sizeof(Student_t),SEEK_SET);
  Student_t st;
  fread(&st,sizeof(Student_t),1,fin);
  printf("Student: %s,%d,%f\n",st.nume,st.varsta,st.nota);
}

void scriereFisierText(FILE *fout,Student_t v[SIZE],int n)
{
  for(int i=0;i<n;i++)
    {
      fprintf(fout,"Student %d:%s,%d,%f\n",i,v[i].nume,v[i].varsta,v[i].nota); 
    }
}
