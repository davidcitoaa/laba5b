#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>
#include "malloc.h"
#include "libs/algorithms/array/array.h"
#include <stdint.h>
#include "math.h"
#include "stdlib.h"

void test_countZeroRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );

    freeMemMatrix(m);
}

//1. Дана квадратная матрица, все элементы которой различны. Поменять местами
//строки, в которых находятся максимальный и минимальный элементы.
void swapRowsMinMax(matrix m) {
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);
    swapRows(m, min.rowIndex, max.rowIndex);
}

//2. Упорядочить строки матрицы по неубыванию наибольших элементов строк
//возвращает максимальный элемент в одномерном массиве а размера n
int getMax(const int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

// сортирует в двумерном массиве по неубыванию максимальные значения в одномерном массиве
void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

//3. Дана прямоугольная матрица. Упорядочить столбцы матрицы по неубыванию
//минимальных элементов столбцов:

//возвращает минимальный элемент в одномерном массиве а размера n
int getMin(const int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i)
        if (a[i] < min)
            min = a[i];
    return min;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

// 4. Если данная квадратная матрица 𝐴 симметрична, то заменить 𝐴 ее квадрат
matrix mulMatrices(matrix m1, matrix m2) {
    matrix saveNewMatrix = getMemMatrix(m1.nRows, m1.nCols);

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m2.nCols; ++j) {
            saveNewMatrix.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; ++k)
                saveNewMatrix.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    }
    return saveNewMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

// 5. Дана квадратная матрица. Если среди сумм элементов строк матрицы нет равных, то транспонировать матрицу

bool isUnique(const int *a, int n) {
    for (int i = 0; i < n; ++i) {
        size_t sumPos = binarySearch(a, n, a[i]);
        if (sumPos != i && sumPos != n)
            return false;
    }
    return true;
}

long long getSum(const int *a, int n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int *a = (int *) calloc(m.nRows, sizeof(int));
    assert(a != NULL);

    for (register size_t i = 0; i < m.nRows; ++i)
        a[i] += getSum(m.values[i], m.nCols);
    if (isUnique(a, m.nRows))
        transposeSquareMatrix(m);
    free(a);
}

//6. Даны две квадратные матрицы 𝐴 и 𝐵. Определить, являются ли они взаимно
//обратными (𝐴 = 𝐵−1).

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix mul = mulMatrices(m1, m2);
    bool res = isEMatrix(mul);
    freeMemMatrix(mul);
    return res;
}

// 7
int getDiagonalIndex(position pos, matrix m) {
    return abs(pos.rowIndex - pos.colIndex - (m.nRows - 1));
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int nDiagonals = m.nRows + m.nCols - 1;
    int diagonalMaxes[nDiagonals];
    for (int i = 0; i < nDiagonals; ++i)
        diagonalMaxes[i] = INT32_MIN;
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j) {
            position elementPos = {i, j};
            int element = m.values[i][j];
            int diagonalIndex = getDiagonalIndex(elementPos, m);
            if (element > diagonalMaxes[diagonalIndex])
                diagonalMaxes[diagonalIndex] = element;
        }
    return getSum(diagonalMaxes, nDiagonals) - diagonalMaxes[m.nRows - 1];
}

// 8
int getMinInArea(matrix m) {
    position maxIndex = getMaxValuePos(m);
    int minValue = m.values[maxIndex.rowIndex][maxIndex.colIndex];
    int left = maxIndex.colIndex;
    int right = maxIndex.colIndex;
    for (int i = maxIndex.rowIndex; i >= 0; i--) {
        for (int j = left; j < right; j++)
            if (m.values[i][j] < minValue)
                minValue = m.values[i][j];
        right = right < m.nCols ? right + 1 : right;
        left = left > 0 ? left - 1 : left;
    }
    return minValue;
}

// 9
float getDistance(int *a, int n) {
    float sumOfSquares = 0;
    for (int i = 0; i < n; ++i) {
        sumOfSquares += pow(a[i], 2);
    }
    return sqrtf(sumOfSquares);
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, &getDistance);
}

// 10
int cmp(const void *pa, const void *pb) {
    int arg1 = *(const int *) pa;
    int arg2 = *(const int *) pb;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int countNUnique(const int *a, int n) {
    int uniqueElements = n > 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[i - 1])
            uniqueElements++;
    }
    return uniqueElements;
}

int countEqClassesByRowsSum(matrix m) {
    int *sum = (int *) malloc(sizeof(int) * m.nRows);
    if (NULL == sum) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    for (int i = 0; i < m.nRows; ++i)
        sum[i] = (int) getSum(m.values[i], m.nCols);
    qsort(sum, m.nRows, sizeof(int), cmp);
    int countEq = countNUnique(sum, m.nRows);
    free(sum);
    return countEq;
}

// 11

int getNSpecialElement(matrix m) {
    int *colm = (int *) malloc(sizeof(int) * m.nCols);
    if (NULL == colm) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    int *colmSum = (int *) malloc(sizeof(int) * m.nRows);
    if (NULL == colmSum) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    int count = 0;
    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j)
            colm[j] = m.values[j][i];
        int maxInCol = getMax(colm, m.nRows);
        colmSum[i] = (int) getSum(colm, m.nRows);
        if (colmSum[i] - maxInCol < maxInCol)
            count++;
    }
    free(colm);
    free(colmSum);
    return count;
}

// 12
void getRowFromColumn(matrix m, size_t pos, int *array) {
    for (int i = 0; i < m.nRows; ++i)
        array[i] = m.values[i][pos];
}

void swapPenultimateRow(matrix m) {
    position minPos = getMinValuePos(m);
    int colWithMin[m.nRows];
    getRowFromColumn(m, minPos.colIndex, colWithMin);
    for (int i = 0; i < m.nRows; ++i)
        m.values[m.nRows - 2][i] = colWithMin[i];
}

void test_swapRowsMinMax1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );
    swapRowsMinMax(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapRowsMinMax2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    12, 2, 3,
                    4, 555, 6,
                    7, 8, 1
            },
            3, 3
    );
    swapRowsMinMax(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    12, 2, 3,
                    7, 8, 1,
                    4, 555, 6,
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapRowsMinMax3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16
            },
            4, 4
    );
    swapRowsMinMax(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    13, 14, 15, 16,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    1, 2, 3, 4,
            },
            4, 4
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapRowsMinMax() {
    test_swapRowsMinMax1();
    test_swapRowsMinMax2();
    test_swapRowsMinMax3();
}

void test_sortRowsByMaxElement1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    4, 5, 6,
                    7, 8, 9,
                    1, 2, 3
            },
            3, 3
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    4, 25, 6,
                    7, 8, 9,
                    25, 2, 3
            },
            3, 3
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 25, 6,
                    25, 2, 3
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 25,
                    1, 25
            },
            2, 2
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 25,
                    1, 25
            },
            2, 2
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement() {
    test_sortRowsByMaxElement1();
    test_sortRowsByMaxElement2();
    test_sortRowsByMaxElement3();
}

void test_sortColsByMinElement1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    4, 5, 6,
                    7, 8, 9,
                    1, 2, 1
            },
            3, 3
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    4, 6, 5,
                    7, 9, 8,
                    1, 1, 2,
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortColsByMinElement2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 5,
                    2, 5, 1, 2,
                    6, 4, 10, 4
            },
            3, 4
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    2, 3, 5, 5,
                    1, 2, 2, 5,
                    10, 6, 4, 4
            },
            3, 4
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortColsByMinElement3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 1, 2,
                    3, 1, 2,
                    3, 1, 2
            },
            3, 3
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    1, 2, 3,
                    1, 2, 3,
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortColsByMinElement() {
    test_sortColsByMinElement1();
    test_sortColsByMinElement2();
    test_sortColsByMinElement3();
}

void test_getSquareOfMatrixIfSymmetric1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 1, 3,
                    1, 1, 2,
                    3, 2, 2
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    19, 10, 17,
                    10, 6, 9,
                    17, 9, 17,
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_getSquareOfMatrixIfSymmetric2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 1, 3,
                    2, 1, 2,
                    3, 1, 2
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 1, 3,
                    2, 1, 2,
                    3, 1, 2
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_getSquareOfMatrixIfSymmetric3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    0, 1, 0,
                    1, 0, 1
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    2, 0, 2,
                    0, 1, 0,
                    2, 0, 2
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_getSquareOfMatrixIfSymmetric() {
    test_getSquareOfMatrixIfSymmetric1();
    test_getSquareOfMatrixIfSymmetric2();
    test_getSquareOfMatrixIfSymmetric3();
}

void test_transposeIfMatrixHasEqualSumOfRows1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 2,
                    0, 1, 5,
                    1, 0, 4
            },
            3, 3
    );
    transposeIfMatrixHasEqualSumOfRows(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    0, 1, 0,
                    2, 5, 4
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeIfMatrixHasEqualSumOfRows2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 2,
                    0, 1, 5,
                    1, 2, 0
            },
            3, 3
    );
    transposeIfMatrixHasEqualSumOfRows(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 2,
                    0, 1, 5,
                    1, 2, 0
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeIfMatrixHasEqualSumOfRows3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3
    );
    transposeIfMatrixHasEqualSumOfRows(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3
    );
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeIfMatrixHasEqualSumOfRows() {
    test_transposeIfMatrixHasEqualSumOfRows1();
    test_transposeIfMatrixHasEqualSumOfRows2();
    test_transposeIfMatrixHasEqualSumOfRows3();
}

void test_isMutuallyInverseMatrices1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 0,
                    1, 1, 0,
                    3, 0, 1
            },
            3, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    -1, 2, 0,
                    1, -1, 0,
                    3, -6, 1
            },
            3, 3
    );
    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 5, 7,
                    6, 3, 4,
                    5, -2, -3
            },
            3, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, -1, 1,
                    -38, 41, -34,
                    27, -29, 24
            },
            3, 3
    );
    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 4,
                    5, 7
            },
            2, 2
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, -4,
                    -5, 3
            },
            2, 2
    );
    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices4() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 4,
                    5, 7
            },
            2, 2
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, -4,
                    -5, 3
            },
            2, 2
    );
    assert(isMutuallyInverseMatrices(m1, m2) == 0);

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices() {
    test_isMutuallyInverseMatrices1();
    test_isMutuallyInverseMatrices2();
    test_isMutuallyInverseMatrices3();
    test_isMutuallyInverseMatrices4();
}

void test_findSumOfMaxesOfPseudoDiagonal1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            },
            3, 4
    );
    long long sum = 20;
    assert(findSumOfMaxesOfPseudoDiagonal(m1) == sum);

    freeMemMatrix(m1);
}

void test_findSumOfMaxesOfPseudoDiagonal2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    1, 2, 3, 4,
                    1, 2, 3, 4
            },
            3, 4
    );
    long long sum = 15;
    assert(findSumOfMaxesOfPseudoDiagonal(m1) == sum);

    freeMemMatrix(m1);
}

void test_findSumOfMaxesOfPseudoDiagonal3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    1, 0, 1
            },
            3, 3
    );
    long long sum = 1;
    assert(findSumOfMaxesOfPseudoDiagonal(m1) == sum);

    freeMemMatrix(m1);
}

void test_test_findSumOfMaxesOfPseudoDiagonal() {
    test_findSumOfMaxesOfPseudoDiagonal1();
    test_findSumOfMaxesOfPseudoDiagonal2();
    test_findSumOfMaxesOfPseudoDiagonal3();
}

void test_getMinInArea1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 5, 4,
                    7, 3, 6, 11,
                    8, 10, 12, 9
            },
            3, 4
    );
    int res = 1;
    assert(getMinInArea(m1) == res);

    freeMemMatrix(m1);
}

void test_getMinInArea2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    10, 7, 5, 6,
                    3, 11, 8, 9,
                    4, 1, 12, 2
            },
            3, 4
    );
    int res = 5;
    assert(getMinInArea(m1) == res);

    freeMemMatrix(m1);
}

void test_getMinInArea3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    6, 8, 9, 2,
                    7, 12, 3, 4,
                    10, 11, 5, 1
            },
            3, 4
    );
    int res = 6;
    assert(getMinInArea(m1) == res);

    freeMemMatrix(m1);
}

void test_test_getMinInArea() {
    test_getMinInArea1();
    test_getMinInArea2();
    test_getMinInArea3();
}

void test_sortByDistances1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 7, 7,
                    8, 8, 8,
                    1, 1, 1,
            },
            3, 3
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    7, 7, 7,
                    8, 8, 8,
            },
            3, 3
    );

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3,
            },
            3, 3
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 6, 9,
                    4, 5, 6,
                    0, 2, 3,
            },
            3, 4
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0, 2, 3,
                    4, 5, 6,
                    7, 6, 9,
            },
            3, 3
    );

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances() {
    test_sortByDistances1();
    test_sortByDistances2();
    test_sortByDistances3();
}

void test_countEqClassesByRowsSum1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 1,
                    2, 7,
                    5, 4,
                    4, 3,
                    1, 6,
                    8, 0
            },
            6, 2
    );

    assert(countEqClassesByRowsSum(m1) == 3);

    freeMemMatrix(m1);
}

void test_countEqClassesByRowsSum2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 1,
                    6, 0,
                    2, 4,
                    4, 2,
                    7, 6,
                    3, 3
            },
            6, 2
    );

    assert(countEqClassesByRowsSum(m1) == 2);

    freeMemMatrix(m1);
}

void test_countEqClassesByRowsSum() {
    test_countEqClassesByRowsSum1();
    test_countEqClassesByRowsSum2();
}


void test_getNSpecialElement1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    6, 0, 9, 2,
                    7, 12, 3, 4,
                    10, 11, 5, 1
            },
            3, 4
    );
    int res = 3;
    assert(getNSpecialElement(m1) == res);

    freeMemMatrix(m1);
}

void test_getNSpecialElement2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    6, 2, 9, 2,
                    7, 12, 4, 4,
                    10, 11, 5, 2
            },
            3, 4
    );
    int res = 0;
    assert(getNSpecialElement(m1) == res);

    freeMemMatrix(m1);
}

void test_getNSpecialElement3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 0, 9, 2,
                    7, 12, 3, 5,
                    10, 11, 5, 2
            },
            3, 4
    );
    int res = 4;
    assert(getNSpecialElement(m1) == res);

    freeMemMatrix(m1);
}

void test_swapPenultimateRow1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 2, 5,
                    6, 1, 8,
                    2, 14, 9,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 5,
                    2, 1, 14,
                    2, 14, 9,
            },
            3, 3
    );

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapPenultimateRow2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    4, 4, 3,
                    3, 5, 6,
                    2, 3, 9,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    4, 4, 3,
                    4, 3, 2,
                    2, 3, 9,
            },
            3, 3
    );

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapPenultimateRow3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    2, 2, 2,
                    3, 3, 3,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    1, 2, 3,
                    3, 3, 3,
            },
            3, 3
    );

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_getNSpecialElement(){
    test_getNSpecialElement1();
    test_getNSpecialElement2();
    test_getNSpecialElement3();
}

void test_swapPenultimateRow() {
    test_swapPenultimateRow1();
    test_swapPenultimateRow2();
    test_swapPenultimateRow3();
}

void test() {
    test_swapRowsMinMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_test_findSumOfMaxesOfPseudoDiagonal();
    test_test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
}

int main() {
    test();

    return 0;
}