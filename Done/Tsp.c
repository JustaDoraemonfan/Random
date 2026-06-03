#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF 99

int **cost;
int *visited;
int n;
int *path;
int *bestPath;
int minCost = INT_MAX;

void TSP(int currentCity, int count, int currentCost)
{
    if (count == n)
    {
        if (cost[currentCity][0] != 0)
        {
            int totalCost = currentCost + cost[currentCity][0];
            if (minCost > totalCost)
            {
                minCost = totalCost;
                for (int i = 0; i < n; i++)
                {
                    bestPath[i] = path[i];
                }
                bestPath[n] = 0;
            }

            return;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && cost[currentCity][i] != 0)
        {
            path[count] = i;
            visited[i] = 1;
            TSP(i, count + 1, currentCost + cost[currentCity][i]);
            visited[i] = 0;
        }
    }
}

int main()
{
    printf("Enter the number of cities : ");
    scanf("%d", &n);
    cost = (int **)malloc(n * sizeof(int *));
    path = (int *)malloc((n + 1) * sizeof(int));
    bestPath = (int *)malloc((n + 1) * sizeof(int));
    visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        cost[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Enter the vertex : \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    visited[0] = 1;
    path[0] = 0;
    TSP(0, 1, 0);
    printf("Total Cost from %d : %d \n", 0, minCost);
    for (int i = 0; i <= n; i++)
    {
        printf("%d", bestPath[i]);
        if (i < n)
            printf(" -> ");
    }
    printf("\n");
    for (int i = 0; i < n; i++)
        free(cost[i]);
    free(cost);
    free(visited);
}