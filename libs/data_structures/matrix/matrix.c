#include "matrix.h"
#include <stdio.h>
#include "malloc.h"
#include "array.h"

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    free(m.values);
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        free(ms->values[i]);
    }
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            scanf("%d", &m.values[i][j]);
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(ms[i]);
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    int *t = m.values[i1 - 1];
    m.values[i1 - 1] = m.values[i2 - 1];
    m.values[i2 - 1] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++) {
        int t = m.values[i][j1 - 1];
        m.values[i][j1 - 1] = m.values[i][j2 - 1];
        m.values[i][j2 - 1] = t;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *arrayForCriteria = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; ++i)
        arrayForCriteria[i] = criteria(m.values[i], m.nRows);
    for (int i = 1; i < m.nRows; i++) {
        int t = arrayForCriteria[i];
        int j = i;
        while (j > 0 && arrayForCriteria[j - 1] > t) {
            swapRows(m, j, j - 1);
            arrayForCriteria[j] = arrayForCriteria[j - 1];
            j--;
        }
        arrayForCriteria[j] = t;
    }
    free(arrayForCriteria);
}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *arrayForCriteria = (int *) malloc(sizeof(int) * m.nCols);
    int *arrayOfColumns = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j)
            arrayOfColumns[j] = m.values[i][j];
        arrayForCriteria[i] = criteria(arrayOfColumns, m.nCols);
    }
    free(arrayOfColumns);

    for (int i = 1; i < m.nRows; i++) {
        int t = arrayForCriteria[i];
        int j = i;
        while (j > 0 && arrayForCriteria[j - 1] > t) {
            swapColumns(m, j, j - 1);
            arrayForCriteria[j] = arrayForCriteria[j - 1];
            j--;
        }
        arrayForCriteria[j] = t;
    }
    free(arrayForCriteria);
}