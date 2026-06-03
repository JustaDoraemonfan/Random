#include <stdio.h>
#include <stdlib.h>

int V, E;
int *parent;
int *rankArr;

typedef struct Edge
{
    int u, v, w;
} Edge;

Edge edges[100];

int findParent(int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;
    parent[vertex] = findParent(parent[vertex]);
    return parent[vertex];
}

void unionSet(int a, int b)
{
    a = findParent(a);
    b = findParent(b);

    if (a == b)
        return;

    if (rankArr[a] > rankArr[b])
    {
        parent[b] = a;
    }
    else if (rankArr[a] < rankArr[b])
    {
        parent[a] = b;
    }
    else
    {
        parent[b] = a;
        rankArr[a]++;
    }
}

void Sort()
{
    for (int i = 0; i < E - 1; i++)
    {
        for (int j = 0; j < E - i - 1; j++)
        {
            if (edges[j].w > edges[j + 1].w)
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal()
{
    int mst = 0;
    int EdgeCount = 0;

    Sort();

    for (int i = 0; i < E && EdgeCount < V - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int pu = findParent(u);
        int pv = findParent(v);

        if (pu != pv)
        {
            unionSet(pu, pv);
            mst += edges[i].w;
            EdgeCount++;
            printf("Edge Taken: %d -> %d  Weight: %d\n", u, v, edges[i].w);
        }
    }

    printf("Total MST Weight = %d\n", mst);
}

int main()
{
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    parent = (int *)malloc(V * sizeof(int));
    rankArr = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rankArr[i] = 0;
    }

    printf("\nEnter edges (source destination weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    kruskal();

    free(parent);
    free(rankArr);

    return 0;
}