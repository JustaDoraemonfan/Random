#include<stdio.h>
#include <stdlib.h>
int **queens;
int n;
int isSafe(int row, int col) {
    for(int i=0; i<col; i++) {
        if(queens[row][i] == 1) return 0;
    }
    for(int i=row, j=col; i>=0 && j>=0; i--, j--) {
        if(queens[i][j] == 1) return 0;
    }
    for(int i=row, j=col; i<n && j>=0; i++, j--) {
        if(queens[i][j] == 1) return 0;
    }
    return 1;
}
void printSolution() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(queens[i][j] == 1) printf(" Q ");
            else printf(" . ");
        }
        printf("\n");
    }
    printf("\n\n");
}
void nqueensSolve(int col) {
    if(col == n) {
        printSolution();
        return;
    }
    for(int i=0; i<n; i++) {
        if(isSafe(i, col)) {
            queens[i][col] = 1;
            nqueensSolve(col + 1);
            queens[i][col] = 0;
        }
    }
}
int main() {
    printf("Enter the number of queens : ");
    scanf("%d", &n);
    queens = (int**)malloc(n * sizeof(int*));
    for(int i=0; i<n; i++) {
       queens[i] = (int*)malloc(n * sizeof(int));
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            queens[i][j] = 0;
        }
    }
    nqueensSolve(0);
    for (int i = 0; i < n; i++) free(queens[i]);
    free(queens);
}