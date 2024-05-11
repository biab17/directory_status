#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Bin.h"

void citire(char *fis,Student_t v[SIZE],int *n)
{
  FILE *fin = fopen(fis,"rb");
  if(fin==NULL)
    {
      printf("Eroare deschidere fisier");
       exit(-1);
    }
  int i=0;
  while(1)
    {
      if(fread(&v[i],sizeof(Student_t),1,fin)!=1)
	break;
      i++;
    }
  (*n)= i;
  fclose(fin);
}

void afisare(Student_t v[SIZE],int n)
{
  for(int i=0;i<n;i++)
    {
      printf("%s %d %f\n",v[i].nume,v[i].varsta,v[i].nota);
    }
}

void scriereFisierBinar(char *fis,Student_t v[SIZE],int n)
{
  FILE *fout = fopen(fis,"wb");
  if(fout==NULL)
    {
      printf("Eroare deschidere fisier scriere");
      exit(-1);
    }
  fwrite(v,sizeof(Student_t),n,fout);
  fclose(fout);
}


void cautare(char *fis,int indx)
{
  FILE *fin = fopen(fis,"rb");
  if(fin==NULL)
    {
      printf("Eroare deschidere fisier citire\n");
      exit(-1);
    }
  fseek(fin,indx * sizeof(Student_t),SEEK_SET);
  Student_t st;
  fread(&st,sizeof(Student_t),1,fin);
  printf("Student: %s,%d,%f\n",st.nume,st.varsta,st.nota);
  fclose(fin);
}

void scriereFisierText(char *fis,Student_t v[SIZE],int n)
{
  FILE *fout = fopen(fis,"w");
  if(fout==NULL)
    {
      printf("eroare deschidere fisier scriere");
      exit(-1);
    }
  for(int i=0;i<n;i++)
    {
      fprintf(fout,"Student %d:%s,%d,%f\n",i,v[i].nume,v[i].varsta,v[i].nota); 
    }
  fclose(fout);
}
