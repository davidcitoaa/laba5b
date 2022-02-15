#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>

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



int main() {
    matrix m = getMemMatrix(3, 3);
//    matrix n = getMemMatrix(2, 2);
//    matrix *a = getMemArrayOfMatrices(2, 2, 2);
//    inputMatrices(&m, 1);
    inputMatrix(m);
//    printf("%d\n", areTwoMatricesEqual(a[0], a[1]));
//    swapColumns(m, 1, 2);
//    printf("%d\n", isEMatrix(m));
    transposeSquareMatrix(m);
    outputMatrix(m);

    return 0;
}
