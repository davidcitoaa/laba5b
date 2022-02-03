#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"

int main() {
    vector v = createVector(10);
    reserve(&v, 8);
//    deleteVector(&v);
    v.data[0] = 2;
    v.data[2] = 15;
    printf("%d %d %d", v.data[0], v.data[2], v.data[1]);

    return 0;
}