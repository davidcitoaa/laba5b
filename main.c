#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "assert.h"

void test_pushBack_fullVector1() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);

    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
}

void test_pushBack_fullVector2() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);

    assert(v.size == 3);
    assert(v.capacity == 4);
    assert(isFull(&v) == 0);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
    assert(v.data[2] == 3);
}

void test_pushBack_fullVector3() {
    vector v = createVector(1);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);

    assert(v.size == 1);
    assert(v.capacity == 1);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
}

void test_pushBack_fullVector4() {
    vector v = createVector(0);
    assert(isEmpty(&v) == 1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    pushBack(&v, 3);
    shrinkToFit(&v);

    assert(v.size == 3);
    assert(v.capacity == 3);
    assert(isFull(&v) == 1);
    assert(v.data[0] == 1);
    assert(v.data[1] == 2);
    assert(v.data[2] == 3);
}

void test_pushBack_emptyVector1() {
    vector v = createVector(1);
    pushBack(&v, 1);
    assert(v.data[0] == 1);
    popBack(&v);

    assert(isEmpty(&v) == 1);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_pushBack_emptyVector2() {
    vector v = createVector(0);
    pushBack(&v, 1);
    pushBack(&v, 14);
    pushBack(&v, 12);

    assert(isEmpty(&v) == 0);
    assert(v.size == 3);
    assert(v.capacity == 4);
    assert(v.data[0] == 1);
    assert(v.data[1] == 14);
    assert(v.data[2] == 12);
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
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert (v.size == 1);
    popBack(&v);
    assert (v.size == 0);
    assert (v.capacity == 1);
}

void test_atVector_notEmptyVector1() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(&(v.data[0]) == atVector(&v, 0));
}

void test_atVector_notEmptyVector2() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 11);
    pushBack(&v, 12);
    assert(&(v.data[2]) == atVector(&v, 2));
    assert(v.data[1] == 11);
}

void test_atVector_notEmptyVector() {
    test_atVector_notEmptyVector1();
    test_atVector_notEmptyVector2();
}

void test_atVector_requestToLastElement1() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 11);
    pushBack(&v, 12);
    assert(&(v.data[2]) == atVector(&v, 2));
    assert(v.data[2] == 12);
}

void test_atVector_requestToLastElement2() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert(&(v.data[0]) == atVector(&v, 0));
    assert(v.data[0] == 10);
}

void test_atVector_requestToLastElement3() {
    vector v = createVector(0);
    pushBack(&v, 10);
    pushBack(&v, 15);
    popBack(&v);

    assert(&(v.data[0]) == atVector(&v, 0));
    assert(v.data[0] == 10);
}

void test_back_oneElementInVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert(&(v.data[0]) == back(&v));
    assert(v.data[0] == 10);
}

void test_back_ElementsInVector1() {
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 2);
    pushBack(&v, 2003);

    assert(&(v.data[2]) == back(&v));
    assert(v.data[2] == 2003);
}

void test_back_ElementsInVector2() {
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 2);
    pushBack(&v, 2003);
    popBack(&v);

    assert(&(v.data[1]) == back(&v));
    assert(v.data[v.size - 1] == 2);
}

void tests_back() {
    test_back_oneElementInVector();
    test_back_ElementsInVector1();
    test_back_ElementsInVector2();
}

void test_atVector_requestToLastElement() {
    test_atVector_requestToLastElement1();
    test_atVector_requestToLastElement2();
    test_atVector_requestToLastElement3();
}

void test_front_oneElementInVector(){
    vector v = createVector(0);
    pushBack(&v, 25);

    assert(&(v.data[0]) == front(&v));
    assert(v.data[0] == 25);
}

void test_front_elementsInVector(){
    vector v = createVector(0);
    pushBack(&v, 25);
    pushBack(&v, 22);
    pushBack(&v, 1);

    assert(&(v.data[0]) == front(&v));
    assert(v.data[0] == 25);
}

void test_front(){
    test_front_oneElementInVector();
    test_front_elementsInVector();
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    tests_back();
    test_front();
}


int main() {
    test();

    return 0;
}