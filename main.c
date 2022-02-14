#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

int main() {
    matrix m = getMemMatrix(2, 2);
    matrix n = getMemMatrix(2, 2);
    matrix *a = getMemArrayOfMatrices(2, 2, 2);
    inputMatrices(a, 2);
//    freeMemMatrix(m);
    swapColumns(a[1], 1, 2);
    outputMatrices(a, 2);

    return 0;
}