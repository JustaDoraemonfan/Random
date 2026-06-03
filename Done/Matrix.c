#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int n;
int *dimensions;
long **mat;
int **split;
void printParenthesis(int i, int j) {
    if(i == j) {
        printf("A%d", i);
        return;
    }
    printf("(");
    printParenthesis(i, split[i][j]);
    printf(" x ");
    printParenthesis(split[i][j] + 1, j);
    printf(")");
}
long matrixMultiplication() {
    for (int i = 0; i < n; i++) {
        mat[i][i] = 0;
    }
    for(int k=2; k<=n; k++) {
        for(int i=0; i<n-k+1; i++) {
            int j = i + k - 1;
            mat[i][j] = LONG_MAX;
            for(int l = i; l<j; l++) {
                long q = mat[i][l] + mat[l+1][j] + dimensions[i] * dimensions[l+1] * dimensions[j+1];
                if(q < mat[i][j]) {
                    mat[i][j] = q;
                    split[i][j] = l;
                }
            }  
        }
    }
    return mat[0][n-1];
}
int main() {
    printf("Enter the number of matrix : ");
    scanf("%d", &n);
    printf("Enter the dimensions : ");
    dimensions = (int*)malloc((n+1) * sizeof(int));
    for(int i=0; i<n+1; i++) {
        scanf("%d", &dimensions[i]);
    }
    mat = (long**)malloc(n * sizeof(long*));
    split = (int**)malloc(n * sizeof(int*));
    for(int i=0; i<n; i++) {
       mat[i] = (long*)malloc(n * sizeof(long));
       split[i] = (int*)malloc(n * sizeof(int));
    }
    long m = matrixMultiplication();
    printf("Total Multiplications : %ld ", m);
    printf("\n\n");
    printParenthesis(0,n-1);
}