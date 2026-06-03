#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF 99

typedef struct Edge
{
    int p, w, index;
    float r;
} Edge;

int capacity;
int n;
Edge edges[100];

void Sort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (edges[j].r < edges[j + 1].r)
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void KnapSack()
{
    float totalProfit = 0;
    Sort();
    for (int i = 0; i < n; i++)
    {
        if (capacity >= edges[i].w)
        {
            totalProfit += edges[i].p;
            capacity -= edges[i].w;
            printf("Item %d Taken: Full\n", edges[i].index);
        }
        else
        {
            float fraction = (float)capacity / edges[i].w;
            totalProfit += fraction * edges[i].p;
            printf("Item %d Taken: %f\n", edges[i].index, fraction);
            break;
        }
    }
    printf("\nTotal Profit = %.2f\n", totalProfit);
}

int main()
{
    printf("Enter the number of Items : ");
    scanf("%d", &n);
    printf("Enter Capacity : ");
    scanf("%d", &capacity);
    printf("Enter the Profit and Weight");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &edges[i].p, &edges[i].w);
        edges[i].r = (float)edges[i].p / edges[i].w;
        edges[i].index = i;
    }
    KnapSack();
}