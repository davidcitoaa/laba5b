#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>
#include "malloc.h"

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
    matrix saveNewMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m2.nCols; ++j) {
            saveNewMatrix.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; ++k) {
                saveNewMatrix.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
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

bool isUnique(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == a[i + 1]) {
            return 0;
        }
    }
    return 1;
}


long long getSum(int *a, int n) {
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

void test() {
    test_swapRowsMinMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
}

int main() {
    test();

    return 0;
}