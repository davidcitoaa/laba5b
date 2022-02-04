#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "assert.h"

void test_pushBack_fullVector1() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    pushBack(&v, 4);

    bool res = v.size == v.capacity;
    assert(res == isFull(&v));
    deleteVector(&v);
}

void test_pushBack_fullVector2() {
    vector v = createVector(0);

    bool res = v.capacity == v.size;
    assert(res == isFull(&v));
    deleteVector(&v);
}

void test_pushBack_fullVector3() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);

    bool res = v.capacity == v.size;
    assert(res == isFull(&v));
    deleteVector(&v);
}

void test_pushBack_fullVector4() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    shrinkToFit(&v);

    bool res = v.capacity == v.size;
    assert(res == isFull(&v));
    deleteVector(&v);
}

void test_pushBack_emptyVector1() {
    vector v = createVector(0);

    bool res = v.size == 0;
    assert(res == isEmpty(&v));
    deleteVector(&v);
}

void test_pushBack_emptyVector2() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);

    bool res = v.size == 0;
    assert(res == isEmpty(&v));
    deleteVector(&v);
}

void test_pushBack_emptyVector3() {
    vector v = createVector(0);
    pushBack(&v, 1);

    bool res = v.size == 0;
    assert(res == isEmpty(&v));
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    test_pushBack_fullVector1();
    test_pushBack_fullVector2();
    test_pushBack_fullVector3();
    test_pushBack_fullVector4();
}


void test_pushBack_emptyVector() {
    test_pushBack_emptyVector1();
    test_pushBack_emptyVector2();
    test_pushBack_emptyVector3();
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert (v.size == 1);
    popBack(&v);
    assert (v.size == 0);
    assert (v.capacity == 1);
    deleteVector(&v);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
}

int main() {
    test();

    return 0;
}