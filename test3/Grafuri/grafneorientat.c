#include "grafneorientat.h"

void initializare(Graf_t *graf)
{
  graf->nr_noduri=0;
  for(int i=0;i<MAX_NOD;i++)
    for(int j=0;j<MAX_NOD;j++)
      {
	graf->arce[i][j]=0;
	graf->arce[j][i]=0;
      }
}

int cautaNod(Graf_t *graf,int cheie)
{
  for(int i=0;i<graf->nr_noduri;i++)
    {
      if(graf->noduri[i].cheie==cheie)
	return i;
    }
  return -1;
}

void insereazaNod(Graf_t *graf,Nod_t nou)
{
  if(graf->nr_noduri==MAX_NOD)
    {
      printf("Nu se mai pot adauga noduri,graful este plin");
      exit(-1);
    }
  int indx=graf->nr_noduri;
  graf->noduri[indx]=nou;
  graf->nr_noduri++;
  for(int i=0;i<graf->nr_noduri;i++)
    {
      graf->arce[indx][i]=0;
      graf->arce[i][indx]=0;
    }
}

void insereazaArc(Graf_t *graf,Arc_t a)
{
  graf->arce[a.nod1.cheie][a.nod2.cheie]=1;
  graf->arce[a.nod2.cheie][a.nod1.cheie]=1;
}


 void suprimaNod(Graf_t *graf, int cheie) {
    int index = -1;
    for (int i = 0; i < graf->nr_noduri; i++) {
        if (graf->noduri[i].cheie == cheie) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Nodul cu cheia %d nu exista.\n", cheie);
        return;
    }

    for (int i = index; i < graf->nr_noduri - 1; i++) {
        graf->noduri[i] = graf->noduri[i + 1];
    }
    graf->nr_noduri--;

    for (int i = index; i < graf->nr_noduri; i++) {
        for (int j = 0; j < graf->nr_noduri + 1; j++) {
            graf->arce[i][j] = graf->arce[i + 1][j];
        }
    }
    for (int j = index; j < graf->nr_noduri; j++) {
        for (int i = 0; i < graf->nr_noduri + 1; i++) {
            graf->arce[i][j] = graf->arce[i][j + 1];
        }
    }
}

void suprimaArc(Graf_t *graf, Arc_t a) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < graf->nr_noduri; i++) {
        if (graf->noduri[i].cheie == a.nod1.cheie) {
            index1 = i;
        }
        if (graf->noduri[i].cheie == a.nod2.cheie) {
            index2 = i;
        }
    }
    if (index1 == -1 || index2 == -1) {
        printf("Unul dintre noduri nu exista in graf.\n");
        return;
    }
    graf->arce[index1][index2] = 0;
    graf->arce[index2][index1] = 0; 
}

void afiseazaGraf(Graf_t *graf) {
    printf("Graful contine %d nod(uri):\n", graf->nr_noduri);

    for (int i = 0; i < graf->nr_noduri; i++) {
        printf("Nod %d: Cheie = %d\n", i, graf->noduri[i].cheie);
    }

    printf("\nMatricea de adiacenta:\n   ");
    for (int i = 0; i < graf->nr_noduri; i++) {
        printf("%3d ", graf->noduri[i].cheie);
    }
    printf("\n");

    for (int i = 0; i < graf->nr_noduri; i++) {
        printf("%3d", graf->noduri[i].cheie);
        for (int j = 0; j < graf->nr_noduri; j++) {
            printf("%3d ", graf->arce[i][j]);
        }
        printf("\n");
    }
}


int minKey(int cheie[], int mstSet[])
{
    int min = INT_MAX, min_index;
    for (int v=0; v<N;v++)
    {
        if (mstSet[v] == 0 && cheie[v] < min)
        {
            min = cheie[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parinte[], int graf[N][N])
{
    printf("Muchiile MST sunt:\n");
    for (int i = 1; i < N; i++)
        printf("%d - %d\n", parinte[i], i);
}

void primMST(int graf[N][N])
{
    int parinte[N]; 
    int cheie[N];   

    int drum[N]; 
    for (int i = 0; i < N; i++)
    {
        cheie[i] = INT_MAX;
        drum[i] = 0;
    }

    cheie[0] = 0;     
    parinte[0] = -1; 

    for (int i=0;i< N-1;i++)
    {
        int nod_ales = minKey(cheie, drum);
        drum[nod_ales] = 1;
        for (int v=0;v<N;v++)
	  {
            if (graf[nod_ales][v] && drum[v] == 0 && graf[nod_ales][v]<cheie[v])
            {
                parinte[v] = nod_ales;
                cheie[v] = graf[nod_ales][v];
            }
        }
    }


    printMST(parinte, graf);
}

