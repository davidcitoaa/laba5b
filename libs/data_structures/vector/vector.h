#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n);

#endif //UNTITLED1_VECTOR_H
