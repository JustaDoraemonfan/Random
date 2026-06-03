#include <stdio.h>

#define N 4
int puzzle[N][N];
int h()
{
    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}};

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j])
            {
                count++;
            }
        }
    }

    return count;
}

void display()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int x, y;

    printf("Enter initial state : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &puzzle[i][j]);

            if (puzzle[i][j] == 0)
            {
                x = i;
                y = j;
            }
        }
    }
    printf("Initial State :\n");
    display();

    while (h() != 0)
    {
        int bestH = 1000;
        int bestX = x, bestY = y;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4)
            {
                int t = puzzle[x][y];
                puzzle[x][y] = puzzle[nx][ny];
                puzzle[nx][ny] = t;

                int a = h();
                if (a < bestH)
                {
                    bestH = a;
                    bestX = nx;
                    bestY = ny;
                }

                t = puzzle[x][y];
                puzzle[x][y] = puzzle[nx][ny];
                puzzle[nx][ny] = t;
            }
        }

        int t = puzzle[x][y];
        puzzle[x][y] = puzzle[bestX][bestY];
        puzzle[bestX][bestY] = t;

        x = bestX;
        y = bestY;
        display();
    }
    printf("Goal state Reached : \n");
    return 0;
}