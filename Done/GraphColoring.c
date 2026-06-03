#include<stdio.h>
#include<stdlib.h>
int **graph;
int *color;
int V;
int m;
int solutions = 0;
int isSafe(int vertex, int c) {
    for(int i=0 ; i<V; i++) {
        if(graph[vertex][i] == 1 && color[i] == c) return 0;
    }
    return 1;
}
void printSolution() {
    solutions++;
    for(int i=0; i<V; i++) {
        printf("Vertex %d : Color %d \n", i+1, color[i]);
    }
    printf("\n\n");
}
void graphColor(int v) {
    if(v == V) {
        printSolution();
        return;
    }
    for(int i=1 ; i<=m; i++) {
        if(isSafe(v, i)) {
            color[v] = i;
            graphColor(v+1);
            color[v] = 0; 
        }
    }
}
int main() {
    printf("Enter the number of Vertices : ");
    scanf("%d", &V);
    graph = (int**)malloc(V * sizeof(int*));
    for(int i=0; i<V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }
    printf("Enter the vertex : \n");
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            scanf("%d", &graph[i][j]);
        }
        
    }
    
    printf("Enter the number of Colors : ");
    scanf("%d", &m);
    color = (int*)malloc(V * sizeof(int));
    for(int i=0; i<m; i++) {
        color[i] = 0;
    }
    graphColor(0);
    printf("\n%d", solutions);
}
