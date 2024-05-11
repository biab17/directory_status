#include"ArboriBinari.h"


int compara(const void *a,const void *b)
{
  const TipNod_t *v1 = (const TipNod_t*)a;
  const TipNod_t *v2 = (const TipNod_t*)b;
  return (v1->varsta - v2->varsta);
}

Node_t makeNod(int cheie,TipNod_t s)
{
  Node_t nou = (Node_t)malloc(sizeof(Arbore_t));
  if(nou == NULL)
    {
      printf("Eroare alocare\n");
      exit(-1);
    }
  nou->cheie = cheie;
  nou->info = s;
  nou->st = NULL;
  nou->dr = NULL;
  return nou;
}

void arbore(Node_t radacina,TipNod_t info,int i,int ok)
{
  if(radacina == NULL)
    radacina = makeNod(i,info);
  else if(radacina->st == NULL)
    radacina->st = makeNod(i,info);
  else if(radacina->dr ==NULL)
    radacina->dr = makeNod(i,info);
  else if(ok==1)
    arbore(radacina->dr,info,i,0);
  else
    arbore(radacina->st,info,i,1);
}

Node_t creare(TipNod_t v[SIZE],int n)
{
  qsort(v,n,sizeof(Student_t),compara);
  Node_t radacina =makeNod(0,v[0]);
  for(int i=1;i<n;i++)
    {
      arbore(radacina,v[i],i,0);
    }
  return radacina;
}


void modificare(Node_t radacina,TipNod_t info,int cheie)
{
  if(radacina == NULL)
    return;
  else
    {
      if(radacina->cheie == cheie)
	{
	  radacina->info = info;
	}
      else
	{
	  modificare(radacina->st,info,cheie);
	  modificare(radacina->dr,info,cheie);
	}
    }
}

int egale(TipNod_t a,TipNod_t b)
{
  if(a.nota==b.nota && a.varsta==b.varsta && !strcmp(a.nume,b.nume))
    return 1;
  return 0;
}

int cautareNod(Node_t radacina,TipNod_t info)
{
  if(radacina!=NULL)
    {
      if(egale(radacina->info,info))
	{
	  return radacina->cheie;
	}
      if(egale(radacina->st->info,info))
	{
	  return radacina->st->cheie;
	}
      if(egale(radacina->dr->info,info))
	{
	  return radacina->dr->cheie;
	}
    }
  cautareNod(radacina->st,info);
  cautareNod(radacina->dr,info);
  return -1;
}

Node_t stergere(Node_t radacina,int cheie)
{
  if(radacina ==NULL)
    return NULL;
  if(radacina->cheie>cheie)
    {
      radacina->st =stergere(radacina->st,cheie);	
	}
      else if(radacina->dr == NULL)
	{
	  Node_t aux = radacina->st;
	  free(radacina);
	  return aux;
	}
      Node_t temp = radacina->dr;
      radacina->cheie=temp->cheie;
      radacina->info=temp->info;
      radacina->dr=stergere(radacina->dr,cheie);
    }
  return radacina;
}

void eliberare(Node_t radacina)
{
  if(radacina!=NULL)
    {
      eliberare(radacina->st);
      eliberare(radacina->dr);
      free(radacina);
    }
}

void preordine(Node_t radacina)
{
  if(radacina!=NULL)
    {
      printf("%d ",radacina->cheie);
      preordine(radacina->st);
      preordine(radacina->dr);
    }
}

void postordine(Node_t radacina)
{
  if(radacina == NULL)
    return;
  postordine(radacina->st);
  postordine(radacina->dr);
  printf("%d ",radacina->cheie);
}

void inordine(Node_t radacina)
{
  if(radacina==NULL)
    return;
  inordine(radacina->st);
  printf("%d ",radacina->cheie);
  inordine(radacina->dr);
}


