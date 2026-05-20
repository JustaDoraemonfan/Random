#include <stdio.h>
#include <stdlib.h>

void printSolution(int **board, int N, int solNo) {
    printf("\nSolution %d:\n", solNo);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) printf("Q ");
            else printf(". ");
        }
        printf("\n");
    }
}

int isSafe(int **board, int N, int row, int col) {
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i] == 1)
            return 0;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return 0;

    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return 0;

    return 1;
}

void solveNQUtil(int **board, int N, int col, int *count) {
    if (col == N) {
        (*count)++;
        printSolution(board, N, *count);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, N, i, col)) {
            board[i][col] = 1;
            solveNQUtil(board, N, col + 1, count);
            board[i][col] = 0;
        }
    }
}

void solveNQueens(int N) {
    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        board[i] = (int *)calloc(N, sizeof(int));
    }

    int count = 0;
    solveNQUtil(board, N, 0, &count);

    if (count == 0)
        printf("\nNo solution exists for N = %d\n", N);
    else
        printf("\nTotal Solutions = %d\n", count);

    for (int i = 0; i < N; i++) free(board[i]);
    free(board);
}

int main() {
    int N;
    printf("Enter no. of queens: ");
    scanf("%d", &N);

    solveNQueens(N);
    return 0;
}
