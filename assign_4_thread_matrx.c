#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int matA[MAX][MAX], matB[MAX][MAX], result[MAX][MAX];
int r1, c1, r2, c2;

void* multiplyRow(void* arg) {
    int row = *(int*)arg;
    for (int i = 0; i < c2; i++) {
        result[row][i] = 0;
        for (int j = 0; j < c1; j++) {
            result[row][i] += matA[row][j] * matB[j][i];
        }
    }
    free(arg);
    pthread_exit(0);
}

int main() {
    printf("Enter rows and columns for matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns for matrix B: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2) {
        printf("Matrix multiplication not possible.\n");
        return -1;
    }

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            scanf("%d", &matA[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            scanf("%d", &matB[i][j]);

    pthread_t threads[r1];
    for (int i = 0; i < r1; i++) {
        int* row = malloc(sizeof(int));
        *row = i;
        pthread_create(&threads[i], NULL, multiplyRow, row);
    }

    for (int i = 0; i < r1; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Resultant matrix:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
