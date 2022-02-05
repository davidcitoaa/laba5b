#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H

#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает структуру-дескриптор вектор из n значений.
vector createVector(size_t n);

// изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t newCapacity);

// – удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

// освобождает память, выделенную под неиспользуемые элементы.
void shrinkToFit(vector *v);

// освобождает память, выделенную вектору
void deleteVector(vector *v);

// возвращает True, если вектор пустой, False в обратном случае
bool isFull(vector *v);

// возвращает True, если вектор полный, False в обратном случае
bool isEmpty(vector *v);

// возвращает i-ый элемент вектора v.
int getVectorValue(vector *v, size_t i);

// добавляет элемент x в конец вектора v
void pushBack(vector *v, int x);

// удаляет последний элемент из вектора v.
void popBack(vector *v);

// возвращает указатель на index-ый элемент вектора.
int* atVector(vector *v, size_t index);

// возвращает указатель на последний элемент вектора
int* back(vector *v);

// возвращает указатель на первый элемент вектора
int* front(vector *v);

#endif //UNTITLED1_VECTOR_H
