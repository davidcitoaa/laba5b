#include "matrix.h"
#include <stdio.h>
#include "malloc.h"
#include "array.h"
#include <stddef.h>
#include "mem.h"

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
    for (int i = 0; i < m.nRows; i++)
        free(m.values[i]);
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(ms[i]);
    free(ms);
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
    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++) {
        int t = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = t;
    }
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int)) {
    float *arrayForCriteria = (float *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; ++i)
        arrayForCriteria[i] = criteria(m.values[i], m.nRows);
    for (int i = 1; i < m.nRows; i++) {
        float t = arrayForCriteria[i];
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

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(const int *, int)) {
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

// TODO изменить сортировку на сортировку выбором
void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(const int *, int)) {
    int *arrayForCriteria = (int *) malloc(sizeof(int) * m.nCols);
    int *arrayOfColumns = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j)
            arrayOfColumns[j] = m.values[j][i];
        arrayForCriteria[i] = criteria(arrayOfColumns, m.nRows);
    }
    free(arrayOfColumns);

    for (int i = 1; i < m.nCols; i++) {
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

bool isSquareMatrix(matrix m) {
    return m.nRows = m.nCols;
}

bool areTwoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;
    for (int i = 0; i < m1.nRows; ++i)
        if (memcmp(m1.values[i], m2.values[i], sizeof(int) * m1.nCols) != 0)
            return false;
    return true;
}

bool isEMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (i == j && m.values[i][j] != 1)
                return false;
    return true;
}

bool isSymmetricMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[i][j] != m.values[j][i])
                return false;
    return true;
}

void transposeSquareMatrix(matrix m) {
    for (int i = 1; i < m.nCols; ++i)
        for (int j = 0; j < i; ++j)
            swap(&m.values[i][j], &m.values[j][i]);
}

position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minIndex.rowIndex = i;
                minIndex.colIndex = j;
            }
    return minIndex;
}

position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxIndex.rowIndex = i;
                maxIndex.colIndex = j;
            }
    return maxIndex;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}


matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

