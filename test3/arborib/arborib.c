#include<stdio.h>
#include<stdlib.h>

#define N 2
#define NN (N*2)

typedef int Cheie_t;

typedef struct Nod
{
  Cheie_t cheie;
  struct Pagina_t *p;
  int contor;
}Nod_t;

typedef struct Pagina_t
{
  int m;//nr elemente ale unei pagini
  struct Pagina_t *p0;
  Nod_t e[NN+1];
}Pagina_t;

Pagina_t* insereaza(Cheie_t cheie,Pagina_t *radacina,Nod_t *nou)
{
  Nod_t nodNou;
  if(!nou)
    {
      nodNou.cheie=cheie;
      nodNou.contor=1;
      nodNou.p=NULL;
    }
  else
    {
      nodNou=*nou;
    }
  if(radacina==NULL)
    {
      radacina=(Pagina_t*)calloc(sizeof(Pagina_t),1);
      radacina->e[++radacina->m]=nodNou;
      return radacina;
    }
  int st=1;
  int dr=radacina->m;
  while(st<=dr)
    {
      int mijloc=(st+dr)/2;
      if(radacina->e[mijloc].cheie==cheie)
	{
	  radacina->e[mijloc].contor++;
	  return radacina;
	}
      if(cheie<radacina->e[mijloc].cheie)
	{
	  dr=mijloc-1;
	}
      else
	{
	  st=mijloc+1;
	}
    }
  int i;
  if(radacina->p0==NULL || nou)
    {
      if(radacina->m<NN)
	{
	  radacina->m++;
	  for(i=radacina->m;i>dr+1;i--)
	    {
	      radacina->e[i]=radacina->e[i-1];
	    }
	  radacina->e[i]=nodNou;
	}
      else
	{
	  Pagina_t *pag1=radacina;
	  Pagina_t *pag2=(Pagina_t*)calloc(sizeof(Pagina_t),1);
	  radacina=(Pagina_t*)calloc(sizeof(Pagina_t),1);
	  for(i=1;i<=N;i++)
	    {
	      pag2->e[i]=pag1->e[i+N];
	    }
	  pag1->m=pag2->m=N;

	  if(nodNou.cheie>pag1->e[N].cheie && nodNou.cheie<pag2->e[N].cheie)
	    {
	      radacina->e[++radacina->m]=nodNou;
	    }
	  else
	    {
	      if(nodNou.cheie<pag1->e[N].cheie)
		{
		  radacina->e[++radacina->m] = pag1->e[N];
		  for(i=pag1->m;i>1 && pag1->e[i-1].cheie>nodNou.cheie;i--)
		    {
		      pag1->e[i]=pag1->e[i-1];
		    }
		  pag1->e[i]=nodNou;
		}
	      else
		{
		  radacina->e[++radacina->m]=pag2->e[1];
		  for(i=1;i<pag2->m && pag2->e[i+1].cheie<nodNou.cheie;i++)
		    {
		      pag2->e[i]=pag2->e[i+1];
		    }
		  pag2->e[i]=nodNou;
		}
	    }
	      pag2->p0=radacina->e[1].p;
	      radacina->p0=pag1;
	      radacina->e[1].p=pag2;      
	}

    }
  else
    {
      Pagina_t *r,*q;
      if(dr==0) q=radacina->p0;
      else q=radacina->e[dr].p;
      r=insereaza(cheie,q,NULL);
      if(r!=q)
	{
	  radacina=insereaza(r->e[1].cheie,radacina,&r->e[1]);
	  free(r);
	}
    }
  return radacina;
}

int cautare(Pagina_t *pag,Cheie_t x)
{
  int st=1,dr=pag->m,mijloc;
  if(pag==NULL) return 0;
  while(st<=dr)
    {
      mijloc=(st+dr)/2;
      if(x==pag->e[mijloc].cheie) return 1;
      if(x<pag->e[mijloc].cheie) dr=mijloc-1;
      else st=mijloc+1;
    }
  
  if(dr==0)
    return cautare(pag->p0,x);
  return cautare(pag->e[dr].p,x);
}

void afisare(Pagina_t *arbore,int nivel)
{
  int i;
  if(!arbore) return;

  afisare(arbore->p0,nivel+1);

  for(i=1;i<=arbore->m;i++)
    afisare(arbore->e[i].p,nivel+1);
  printf("Nivel %d:",nivel);
  for(i=1;i<=arbore->m;i++)
    printf("%d ",arbore->e[i].cheie);
  printf("\n");
}

void vecinStang(Pagina_t *pag, Pagina_t *st, Pagina_t *r, int d)
{
  int i;  
  if (st->m == N)
	{
	  st->e[N + 1] = pag->e[d];
	  st->e[N + 1].p = r->p0;
	  st->m = NN;
	  for (i = N + 2; i <= NN; i++)
	    st->e[i] = r->e[i - N - 1];
	  
	  for (i = d; i < pag->m; i++)
	    pag->e[i] = pag->e[i + 1];
	  pag->m--;
	  free(r);
	}
	else
	{
	 r->m = N;
	 for (i = N; i > 1; i--)
	   r->e[i] = r->e[i - 1];
	 r->e[1] = pag->e[d];
	 r->e[1].p = r->p0;
	 r->p0 = st->e[st->m].p;
	 
	 pag->e[d] = st->e[st->m];
	 pag->e[d].p = r;
	 st->m--;
	}
}

void vecinDrept(Pagina_t *pag, Pagina_t *dr, Pagina_t *r, int d)
{
  int i;

  r->e[N] = pag->e[d + 1];
  r->e[N].p = dr->p0;
  r->m = N;
  
  if (dr->m == N)
	{
	  r->m = NN;
	  for (i = N + 1; i <= NN; i++)
	    r->e[i] = dr->e[i - N];
	  
	  for (i = 1; i < pag->m; i++)
	    pag->e[i] = pag->e[i + 1];
	  pag->m--;
	  free(dr);
	}
	else
	  {
	    pag->e[d + 1] = dr->e[1];
	    pag->e[d + 1].p = dr;
	    
	    dr->p0 = dr->e[1].p;
	    for (i = 1; i < dr->m; i++)
	      dr->e[i] = dr->e[i + 1];
	    dr->m--;
	}
}

Pagina_t* suprima(Pagina_t *pag, Cheie_t x, Nod_t *nod)
{
  int i, s, d, mijloc;
  Pagina_t *q, *r;
      
  if (pag == NULL || pag->m == 0)
    return NULL;
  
  s = 1;
  d = pag->m;
  while (s<=d)
	{
	  mijloc=(s+d)/2;
	  if (x == pag->e[mijloc].cheie)
	    break;
	  if (x < pag->e[mijloc].cheie)
	    d= mijloc-1;
	  else
	    s=mijloc+1;
	}

  if (x == pag->e[mijloc].cheie)
    {
      if (pag->p0 == NULL)
	{
	  if (nod)
	    {
	      q = nod->p;
	      *nod = pag->e[pag->m];
	      nod->p = q;
	    }
	  for (i = mijloc; i < pag->m; i++)
	    pag->e[i] = pag->e[i + 1];
	  pag->m--;

	  for (q = pag; pag && pag->m == 0; free(q), q = pag)
	    pag = pag->p0;
	  
	 return pag;
	}
	 
      return suprima(pag, x - 1, &pag->e[mijloc]);
    }

  if (d==0)
    q = pag->p0;
  else
    q = pag->e[d].p;
  r = suprima(q, x, nod);

  if (r == NULL)
    {
      if (nod)
	return suprima(pag, pag->e[d].cheie, nod);
      else 
	return pag;
	}
  
  if (r->m < N) 
    {
      Pagina_t *st, *dr;
      if (d == 1)
	st = pag->p0;
      else
	st = pag->e[d - 1].p;
      dr = pag->e[d + 1].p;
      
      if (r == pag->p0)
	vecinDrept(pag, dr, r, d);
      else if (d == pag->m) 
	vecinStang(pag, st, r, d);
      else 
	{    
	  if (dr->m > st->m)
	    vecinDrept(pag, dr, r, d);
	  else
	    vecinStang(pag, st, r, d);
	}
    }
  
  for (q = pag; pag && pag->m == 0; free(q), q = pag)
    pag = pag->p0;
  
  return pag;
}




int main()
{
   Pagina_t *radacina;
   int i, n = 18;
   
   radacina = NULL;
   for (i = 1; i <= n; i++)
     radacina = insereaza(i, radacina, NULL);
   
   printf("Arborele-B initial:\n");
   afisare(radacina, 1);
   printf("\n");
   printf("%d\n",cautare(radacina,11));
   for (i = 1; i <= n; i++)
     {
       printf("Dupa stergerea lui %d:\n", i);
       radacina = suprima(radacina, i, NULL);
       afisare(radacina, 1);
       printf("\n\n");
     }
  return 0;
}




