#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int **graph;
int V;
int *visited;
int queue[100];
int fr = 0;
int rear = 0;
void enque(int x)
{
    queue[rear++] = x;
}
int pop()
{
    int popped = queue[fr++];
    return popped;
}

void bfs(int start)
{
    visited[start] = 1;
    enque(start);

    while (fr < rear)
    {
        int node = pop();
        printf("%d ", node);
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && graph[node][i])
            {
                visited[i] = 1;
                enque(i);
            }
        }
    }
}
void dfs(int start)
{
    visited[start] = 1;
    printf("%d ", start);
    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && graph[start][i])
        {
            dfs(i);
        }
    }
}

void visitedReset()
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
}

int main()
{
    printf("Enter the number of vertex : ");
    scanf("%d", &V);
    graph = (int **)malloc(V * sizeof(int *));
    visited = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
    {
        graph[i] = (int *)malloc(V * sizeof(int));
    }
    printf("Enter Node: \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    visitedReset();
    printf("BFS\n");
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            bfs(i);
        }
    }
    visitedReset();
    printf("\nDFS\n");
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
}