#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int *dist;
int *parent;
int V, E;
int source;


typedef struct Edge{
    int u, v, w;
} Edge;

Edge edges[100];

void printPath(int vertex) {
    if(vertex == -1){
        return;
    }
    printPath(parent[vertex]);
    printf("%d ", vertex);
}

void bellmanFord() {
    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[source] = 0;
    for(int i=0; i<V-1; i++) {
        for(int j=0; j<E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
    int negative = 0;
    for(int i=0; i<E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            negative = 1;
            break;
        }
    }
    if(negative) {
        printf("Negative Edge Detected ! ");
        return;
    }else{
        printf("Vertex - <Distance From Source> \n");
        for(int i=0; i<V; i++) {
            if(dist[i] == INT_MAX) printf("%d - INF\n", i);
            else {
                printf("%d - %d\n", i, dist[i]);
                printPath(i);
            }
        }
    }
}


int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    dist = (int*)malloc(V * sizeof(int));
    parent = (int*)malloc(V * sizeof(int));
        
    printf("\nEnter edges (source destination weight):\n");
    for(int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }
    printf("Enter the source vertex : ");
    scanf("%d", &source);
    bellmanFord();
    free(dist);
    free(parent);
}