#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#define INF 99

int **graph;
int *dist;
int *parent;
int *visited;
int V;
int source;

int findMin() {
    int minIndex = -1;
    int minVal = INT_MAX;
    for(int i=0; i<V; i++) {
        if(!visited[i] && dist[i]<minVal) {
            minVal = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void printPath(int vertex) {
    if(vertex == -1) {
        return;
    }
    printPath(parent[vertex]);
    printf("%d ", vertex);
}

void dijkstra() {
    for(int i=0; i<V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;
    for(int i=0; i<V; i++) {
        int u = findMin();
        if(u == -1)break;
        visited[u] = 1;
        for(int v=0; v<V; v++) {
            int w = graph[u][v];
            if(w != 0 && w != INF && w + dist[u] < dist[v]) {
                dist[v] = w + dist[u];
                parent[v] = u;
            }
        }
    }
    printf("\nShortest distances from source %d:\n", source);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) printf("%d -> %d : INF\n", source, i);
        else {
            printf("%d -> %d : %d\n", source, i, dist[i]);
            printPath(i);
            printf("\n");
        }
    }
}

int main() {
    printf("Enter the number of Vertex : ");
    scanf("%d", &V);
    graph = (int**)malloc(V * sizeof(int*));
    for(int i=0; i<V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }
    printf("Enter adjacency matrix (%d for no edge):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    dist = (int*)malloc(V * sizeof(int));
    parent = (int*)malloc(V * sizeof(int));
    visited = (int*)malloc(V * sizeof(int));
    printf("Enter source : ");
    scanf("%d", &source);
    dijkstra();
}