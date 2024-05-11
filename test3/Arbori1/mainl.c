#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 1000

typedef struct
{
  int varsta;
  int copii;
}Student_t;

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

void scriereFisierBinar(FILE *fout,Student_t v[SIZE],int n)
{
  fout=deschidereFisier("test.bin","wb");
  fwrite(v,sizeof(Student_t),n,fout);
}

int cautare(FILE *fin,int varsta)
{
  rewind(fin);
  Student_t st;
  int k=0;
  while(fread(&st,sizeof(Student_t),1,fin)==1)
    {
      k++;
      if(st.varsta==varsta) return k;
    }
  return k;
}

typedef struct Nod_t* Arbore_t;
typedef struct Nod_t
{
  int cheie;
  int index;
  Arbore_t dr;
  Arbore_t st;
}Nod_t;

typedef Student_t TipNod_t;

Arbore_t makeNod(TipNod_t a,int i)
{
  Arbore_t nou = (Arbore_t)malloc(sizeof(TipNod_t));
  if(nou == NULL)
    {
      printf("Eroare alocare\n");
      exit(-1);
    }
  nou->cheie = a.varsta;
  nou->index = i;
  nou->st = NULL;
  nou->dr = NULL;
  return nou;
}

Arbore_t creaza(Arbore_t radacina,TipNod_t a,int i)
{
  if(radacina!=NULL)
    {
      if(a.varsta<radacina->cheie)
	{
	  radacina->st = creaza(radacina->st,a,i);
	}
      else
	{
	  radacina->dr = creaza(radacina->dr,a,i);
	}
    }
  else
    {
      radacina =makeNod(a,i);
    }
  return radacina;
}


void preordine(Arbore_t radacina)
{
  if(radacina!=NULL)
    {
      printf("%d ",radacina->cheie);
      preordine(radacina->st);
      preordine(radacina->dr);
    }
}


void cautareNod(FILE *fin,Arbore_t radacina,int varsta)
{
  rewind(fin);
  if(radacina!=NULL)
    {
      if(radacina->cheie ==varsta)
	{
	  fseek(fin,radacina->index*sizeof(Student_t),SEEK_SET);
	  Student_t aux;
	  fread(&aux,sizeof(Student_t),1,fin);
	  printf("%d\n",aux.copii);
	}
      else
	{
	  cautareNod(fin,radacina->st,varsta);
	  cautareNod(fin,radacina->dr,varsta);
	}
    }
}

int main()
{
  FILE *fout=deschidereFisier("test.bin","wb");
  for(int i=0;i<1000;i++)
    {
      Student_t aux;
      aux.varsta = rand()%1000;
      aux.copii = rand() %500;
      fwrite(&aux,sizeof(Student_t),1,fout);
    }
  fclose(fout);

  FILE *fin=deschidereFisier("test.bin","rb");
  Arbore_t radacina=NULL;
  for(int i=0;i<SIZE;i++)
    {
      Student_t aux;
      fread(&aux,sizeof(Student_t),1,fin);
      radacina=creaza(radacina,aux,i);
    }
  preordine(radacina);
  printf("\n");
  int n;
  scanf("%d",&n);
  printf("%d\n",cautare(fin,n));
  cautareNod(fin,radacina,n);
  fclose(fin);
  return 0;
}
