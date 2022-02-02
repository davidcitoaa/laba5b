#include <stdio.h>

static void getMaxLastPosition_(int *maxPos, int i, int *xMax) {
    int x;
    scanf("%d", &x);

    if (x == 0)
        return;
    else {
        if (x >= *xMax) {
            *xMax = x;
            *maxPos = i;
        }
        getMaxLastPosition_(maxPos, i + 1, xMax);
    }
}

int getMaxLastPosition() {
    int xMax;
    scanf("%d", &xMax);

    if (xMax == 0)
        return -1;
    int maxPos = 0;
    getMaxLastPosition_(&maxPos, 1, &xMax);
    return maxPos;
}

int binarySearchLessX(const int *a, const size_t n, int x) {
    x--;
    int left = -1;
    int right = n;
    while (right - left > 1) {
        int middle = left + (right - left)/2;
        if (a[middle] <= x)
            left = middle;
        else
            right = middle;
    }
    return left;
}

int main() {
//    printf("%d", getMaxLastPosition());
//    int a[3];
//    a[0] = 1;
//    a[1] = 2;
//    a[2] = 3;
//    printf("%d\n", binarySearchLessX(a, 3, 2));
//    printf("%d\n", 01);
    int b = 10;
    for (int b = 0; b < 2; b++)
        printf("%d ", b);
    printf("%d", b);

    return 0;
}