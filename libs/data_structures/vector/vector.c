#include <stdio.h>
#include "vector.h"
#include "malloc.h"
#include "stdlib.h"

vector createVector(size_t n) {
    vector result = {(int *) malloc(sizeof(int) * n), 0, n};
    if (result.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return result;
}

void reserve(vector *v, const size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else
        v->data = (int *) realloc(v->data, newCapacity);
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    if (v->size > newCapacity)
        v->size = newCapacity;
    v->capacity = newCapacity;
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v){
    reserve(v, v->size);
}

void deleteVector(vector *v){
    free(v->data);
}

