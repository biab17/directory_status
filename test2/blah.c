#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Se da un fisier CSV 'in.txt' cu liniii de forma:
Pere,8.3
Kiwi,9
Mere,5.2
Se cere sa se sorteze dupa numele produsului si sa se scrie in fisieru; 'out.txt'
Se va folosi minimul de memorie necesara pentru oricate produse din fisier
*/

int split(char *str,char sep,char* c[])
{
  int n=0;
  char *p=str;//iterator in str
  c[n++]=p;   //primul loc liber in vector se afla la pozitia n,asa ca adaugam la pozzitia n,apoi trecem la urmatoare => postincrementare
  /*for(;;)
    {
      if(*p==sep)
	{
	  *p='\0';
	  c[n++]=p+1;
	}
      else if(*p=='\0'){
	break;
      }
      p++;
    }varianta 1
  */
  for(char *p=str;*p;p++)
    {
      if(*p==sep)
	{
	  *p='\0';
	  c[n++]=p+1;
	}
    }
  
  return n;
}

typedef struct{
  char *nume;
  float pret;
}Produs;

Produs *produse=NULL;
int nProduse=0;

void add(char *nume,float pret)
{
  size_t n=strlen(nume)+1;
  char *s=(char*)malloc(n*sizeof(char));
  strcpy(s,nume);
  if(s==NULL)
      {
	puts("memorie insuficienta");
	exit(1);
      }
  Produs *aux=(Produs*)realloc(produse,(nProduse+1)*sizeof(Produs));
  if(aux==NULL)
    {
      	puts("memorie insuficienta");
	exit(1);
    }
  produse=aux;
  Produs p;
  p.nume=s;
  p.pret=pret;
  produse[nProduse++]=p;
}

void citire(char *fisName)
{
  FILE *fis=fopen(fisName,"r");
  if(fis==NULL)
    {
      puts("Nu s-a deschis fisierul\n");
      exit(1);
    }
  char buf[1000];
  while(fgets(buf,1000,fis)!=0)
    {
      // puts(buf);
      char *c[10];
      int n=split(buf,',',c);
      if(n==2)
	{
	  //  printf("%s|%s\n",c[0],c[1]);
	  add(c[0],atof(c[1]));  // atof=ascii to float
	}
    }
  fclose(fis);
}

void scriere(char *fisName)
{
  FILE *fis=fopen(fisName,"w");
  if(fis==NULL)
    {
      puts("Nu s-a deschis fisierul\n");
      exit(1);
    }
  for(int i=0;i<nProduse;i++)
    {
      fprintf(fis,"%s,%g\n",produse[i].nume,produse[i].pret);
    }
  fclose(fis);
}

void sortare()
{
  int schimbare;
  do{
    schimbare=0;
    for(int i=1;i<nProduse;i++)
      {
	if(strcmp(produse[i-1].nume,produse[i].nume)>0)
	  {
	    Produs aux=produse[i-1];
	    produse[i-1]=produse[i];
	    produse[i]=aux;
	    schimbare=1;
	  }
      }
  }while(schimbare);
}

int main()
{
  citire("in.txt");
  sortare();
  scriere("out.txt");
  return 0;
}
