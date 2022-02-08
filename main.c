#include <stdio.h>
#include "libs/data_structures/vector/vectorVoid.h"
#include "assert.h"
#include "malloc.h"

void rest_pushBackV_emptyVector() {
    vectorVoid v = createVectorV(0, sizeof(char));
    char a = 15;
    pushBackV(&v, &a);
    char b = 2;
    pushBackV(&v, &b);
    char c;
    getVectorValueV(&v, 1, &c);

    assert(b == c);
    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(c == 2);
}

void rest_pushBackV_fullVector() {
    vectorVoid v = createVectorV(0, sizeof(char));
    char a = 15;
    pushBackV(&v, &a);
    char b = 2;
    pushBackV(&v, &b);
    char c;
    getVectorValueV(&v, 1, &c);

    assert(b == c);
    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(c == 2);
}

void test_popBackV_notEmptyVector() {
    vectorVoid v = createVectorV(0, sizeof(char));
    int a = 5;
    pushBackV(&v, &a);
    int b = 6;
    pushBackV(&v, &b);
    popBackV(&v);
    int c = 20;
    pushBackV(&v, &c);
    int d = 25;
    pushBackV(&v, &d);
    popBackV(&v);
    int y;
    getVectorValueV(&v, 0, &y);

    assert(y == a);
    assert(v.size == 2);
    assert(v.capacity == 4);
    assert(isEmptyV(&v));
}

void test() {
    rest_pushBackV_emptyVector();
}

int main() {
    test();

    return 0;
}