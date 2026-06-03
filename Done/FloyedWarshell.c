#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#define INF 99

int **graph;
int **next;
int V;

void printPath(int u, int v) {
    if(next[u][v] == -1) printf("No Path\n");
    printf("%d ", u);
    while(u != v) {
        u = next[u][v];
        printf("%d ", u);
    }
}

void matrixPrint() {
    for(int i=0;i <V; i++) {
        for(int j=0; j<V; j++) {
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }
}

void floyed() {
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            if(i==j) {
                graph[i][j] = 0;
                next[i][j] = j;
            }
            else if(graph[i][j] != INF) {
                next[i][j] = j;
            }
            else {
                next[i][j] = -1;
            }
        }
    }
    for(int k=0; k<V; k++) {
        for(int i=0; i<V; i++) {
            for(int j=0; j<V; j++) {
                if(graph[i][k] != INF && graph[k][j] != INF && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
        matrixPrint();
    }
}

int main() {
    printf("Enter the number of Vertex : ");
    scanf("%d", &V);
    graph = (int**)malloc(V * sizeof(int*));
    next = (int**)malloc(V * sizeof(int*));
    for(int i=0; i<V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        next[i] = (int*)malloc(V * sizeof(int));
    }
    printf("Enter adjacency matrix (%d for no edge):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    floyed();
    printf("Final Cost Matrix : \n");
    matrixPrint();
    printf("Vertex : Distance\n");
    printPath(0, V-1);
    printf("\nMinimum Distance : %d", graph[0][V-1]);
}