#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "array.h"

void inputArray(int *a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

size_t linearSearch(const int *a, const size_t n, const int x) {
    for (size_t i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return n;
}

int getCountOfElementsIf(const int *a, const size_t n, int (*f)(int)) {
    int count = 0;
    for (size_t i = 0; i < n; i++)
        if (f(a[i]))
            count++;
    return count;
}

void deleteIf(int *a, size_t *n, int (*f)(int)) {
    size_t iRead = 0;
    while (iRead < *n && !f(a[iRead]))
        iRead++;
    size_t iWrite = iRead;
    while (iRead < *n) {
        if (!f(a[iRead])) {
            a[iWrite] = a[iRead];
            iWrite++;
        }
        iRead++;
    }
    *n = iWrite;
}

void insert(int *a, size_t *n, const size_t pos, const int x) {
    for (size_t i = *n - 1; i >= pos; i--)
        a[i + 1] = a[i];
    a[pos] = x;
    (*n)++;
}


void insertionSort(int *a, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void deleteByPosSaveOrder(int *a, size_t *n, const size_t pos) {
    for (size_t i = pos; i < *n - 1; i++)
        a[i] = a[i + 1];
    (*n)--;
}

void deleteByPosNotKeepingOrder(int *a, size_t *n, const size_t pos) {
    a[pos] = a[*n - 1];
    (*n)--;
}

void append(int *a, size_t *n, const int x) {
    a[*n] = x;
    (*n)++;
}

void forEach(int *a, const size_t n, int (*f)(int)) {
    for (size_t i = 0; i < n; i++)
        a[i] = f(a[i]);
}

int any(const int *a, const size_t n, int (*f)(int)) {
    for (size_t i = 0; i < n; i++) {
        if (f(a[i]))
            return 1;
    }
    return 0;
}

int all(const int *a, const size_t n, int (*f)(int)) {
    for (size_t i = 0; i < n; i++) {
        if (!f(a[i]))
            return 0;
    }
    return 1;
}

size_t binarySearch(const int *a, size_t n, int x) {
    size_t left = 0;
    size_t right = n - 1;
    while (left <= right) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else
            return middle;
    }
    return n;
}

size_t binarySearchMoreOrEqual(const int *a, const size_t n, const int x) {
    int left = -1;
    int right = n;
    while (right - left > 1) {
        int middle = left + (right - left) / 2;
        if (a[middle] >= x)
            right = middle;
        else
            left = middle;
    }
    return right != -1 ? right + 1 : n + 1;
}

int getFirstNegativeIndex(const int *a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        if (a[i] < 0)
            return i;
    return -1;
}

int getFirstIndexOfElementIf(const int *a, const size_t n, int (*f)(int)) {
    for (size_t i = 0; i < n; i++)
        if (f(a[i]))
            return i;
    return -1;
}

int getLastEvenIndex(const int *a, const size_t n) {
    for (size_t i = n - 1; i >= 0; i--)
        if (a[i] % 2 == 0)
            return i;
    return -1;
}

int getLastIndexOfElementIf(const int *a, const size_t n, int (*f)(int)) {
    for (size_t i = n; i > 0; i--)
        if (f(a[i - 1]))
            return i - 1;
    return -1;
}

int countOfNegativeElements(const int *a, const size_t n) {
    int count = 0;
    for (size_t i = 0; i < n; i++)
        count += (a[i] < 0);
    return count;
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void reverseArray(int *a, const size_t n) {
    int middleOfArray = n / 2;
    for (size_t i = 0; i < middleOfArray; i++)
        swap(&a[i], &a[n - i - 1]);
}

int isPalindrome(const int *a, const size_t n) {
    int middleOfArray = n / 2;
    for (size_t i = 0; i < middleOfArray; i++) {
        if (a[i] != a[n - i - 1])
            return 0;
    }
    return 1;
}

int isDecreasing(const int x, const int y) {
    return x > y;
}

int isIncreasing(const int x, const int y) {
    return x < y;
}

void selectionSort(int *a, const size_t n, int (*f)(int, int)) {
    for (size_t i = 0; i < n - 1; i++) {
        size_t index = i;
        for (size_t j = i + 1; j < n; j++)
            if (f(a[j], a[index]))
                index = j;
        if (index != i)
            swap(&a[i], &a[index]);
    }
}

int cyclicShift(int *a, const size_t n, size_t k) {
    k %= n;
    while (k--) {
        int tmp = a[0];
        for (size_t i = 0; i < n - 1; ++i)
            a[i] = a[i + 1];
        a[n - 1] = tmp;
    }
}

int abs(int x) {
    return x >= 0 ? x : -x;
}

void arraySplit(const int *a, const size_t sizeA, int *b, size_t *sizeB, int
*c, size_t *sizeC, int (*f)(int)) {
    for (size_t i = 0; i < sizeA; i++) {
        if (f(a[i]))
            append(b, sizeB, a[i]);
        else
            append(c, sizeC, a[i]);
    }
}

