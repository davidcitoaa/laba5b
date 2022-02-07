#include "vectorVoid.h"
#include <stdio.h>
#include "malloc.h"
#include "stdlib.h"
#include <stdbool.h>
#include "assert.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid result = {(int *) malloc(baseTypeSize * n), 0, n, baseTypeSize};
    if (result.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return result;
}

void reserveV(vectorVoid *v, const size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else
        v->data = (int *) realloc(v->data, v->baseTypeSize * newCapacity);
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    if (v->size > newCapacity)
        v->size = newCapacity;
    v->capacity = newCapacity;
}

void shrinkToFitV(vectorVoid *v) {
    reserveV(v, v->size);
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
}
