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
