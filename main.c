#include <stdio.h>
#include "libs/data_structures/vector/vectorVoid.h"
#include "assert.h"
#include "malloc.h"


int main() {
    vectorVoid v = {(int *) malloc(5 * sizeof(float)), 5, 10, sizeof(float)};

    
    return 0;
}