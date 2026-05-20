#include <stdio.h>
#include <stdlib.h>

int isSafe(int v, int **graph, int V, int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] == 1 && color[i] == c)
            return 0;
    }
    return 1;
}

void printSolution(int color[], int V, int solNo) {
    printf("\nSolution %d:\n", solNo);
    for (int i = 0; i < V; i++) {
        printf("Node %d -> Color %d\n", i + 1, color[i]);
    }
}

void graphColoringUtil(int **graph, int V, int m, int color[], int v, int *count) {
    if (v == V) {
        (*count)++;
        printSolution(color, V, *count);
        return; // IMPORTANT: return but do NOT stop overall, we want ALL solutions
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, V, color, c)) {
            color[v] = c;
            graphColoringUtil(graph, V, m, color, v + 1, count);
            color[v] = 0; // backtrack
        }
    }
}

void graphColoring(int **graph, int V, int m) {
    int *color = (int *)calloc(V, sizeof(int));
    int count = 0;

    graphColoringUtil(graph, V, m, color, 0, &count);

    if (count == 0)
        printf("\nNo solution exists for %d colors.\n", m);
    else
        printf("\nTotal Solutions = %d\n", count);

    free(color);
}

int main() {
    int V, m;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter number of colors (m): ");
    scanf("%d", &m);

    graphColoring(graph, V, m);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
