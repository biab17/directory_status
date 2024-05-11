#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
  int src, dest, weight;
}Edge;


typedef struct Subset
{
  int parent;
  int rank;
} Subset;


typedef struct Graph
{
  int N, L; 
  Edge* edge;
} Graph;


Graph* createGraph(int N, int L)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->N = N;
    graph->L = L;
    graph->edge = (Edge*)malloc(L * sizeof(Edge));
    return graph;
}


int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
      {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
      }
}


int compare(const void* a, const void* b)
{
    Edge* a_edge = (Edge*)a;
    Edge* b_edge = (Edge*)b;
    return a_edge->weight - b_edge->weight;
}

void KruskalMST(Graph* graph)
{
    int N = graph->N;
    Edge result[N]; 
    int e = 0; 
    int i = 0; 

    qsort(graph->edge, graph->L, sizeof(graph->edge[0]), compare);

    Subset* subsets = (Subset*)malloc(N * sizeof(Subset));

   
    for (int v = 0; v < N; ++v)
      {
        subsets[v].parent = v;
        subsets[v].rank = 0;
      }


    while (e < N - 1 && i < graph->L)
      { 
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

   
    printf("Following are the edges in the constructed MST:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
}

int main() {
    int N = 4; 
    int L = 5; 
    Graph* graph = createGraph(N, L);

   
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

   
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

 
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;


    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}
