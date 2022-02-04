#include <stdio.h>
#include "vector.h"
#include "malloc.h"
#include "stdlib.h"
#include <stdbool.h>

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
        v->data = (int *) realloc(v->data, sizeof(int) * newCapacity);
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

bool isEmpty(vector *v){
    return v->size == 0;
}

bool isFull(vector *v){
    return v->size == v->capacity;
}

int getVectorValue(vector *v, const size_t i){
    return v->data[i];
}

void pushBack(vector *v, int x){
    if (v->capacity == 0)
        reserve(v, 1);
    else if (v->size == v->capacity)
        reserve(v, v->size * 2);
    v->data[v->size++] = x;
}

void popBack(vector *v){
    if (isEmpty(v)) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v->size--;
}