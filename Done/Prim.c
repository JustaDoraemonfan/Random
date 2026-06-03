#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF 99

int *dist;
int *parent;
int *inMst;
int V;
int **graph;
int source;

int findMin()
{
    int minIndex = -1;
    int minVal = INT_MAX;

    for (int i = 0; i < V; i++)
    {
        if (!inMst[i] && dist[i] < minVal)
        {
            minVal = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void printPath(int vertex)
{
    if (vertex == -1)
        return;
    printPath(parent[vertex]);
    printf("%d ", vertex);
}

void prim()
{
    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        inMst[i] = 0;
        dist[i] = INT_MAX;
    }

    dist[source] = 0;

    for (int i = 0; i < V; i++)
    {
        int u = findMin();
        if (u == -1)
            break;

        inMst[u] = 1;

        for (int v = 0; v < V; v++)
        {
            int w = graph[u][v];

            if (w != 0 && w != INF && !inMst[v] && w < dist[v])
            {
                dist[v] = w;
                parent[v] = u;
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
        {
            printf("Source - %d - No Path\n", i);
        }
        else
        {
            printf("Source - %d Weight : %d Path: ", i, dist[i]);
            printPath(i);
            printf("\n\n");
        }
    }
}

int main()
{
    printf("Enter the number of Vertex : ");
    scanf("%d", &V);

    graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    printf("Enter adjacency matrix (%d for no edge):\n", INF);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    dist = (int *)malloc(V * sizeof(int));
    parent = (int *)malloc(V * sizeof(int));
    inMst = (int *)malloc(V * sizeof(int));

    printf("Enter source : ");
    scanf("%d", &source);

    prim();

    free(dist);
    free(parent);
    free(inMst);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}