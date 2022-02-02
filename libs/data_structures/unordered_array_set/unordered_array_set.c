#include <stdio.h>
#include <assert.h>
#include "unordered_array_set.h"

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0,
                                  capacity};
}

size_t unordered_array_set_in(const unordered_array_set set, const int value) {
    return linearSearch(set.data, set.size, value);
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(*set, value) == set->size)
        append(set->data, &set->size, value);
}

void unordered_array_set_print(unordered_array_set set) {
    printf("{");
    for (int i = 0; i < set.size; i++)
        printf("%d, ", set.data[i]);

    if (set.size == 0)
        printf("}\n");
    else
        printf("\b\b}\n");
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    return set;
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size)
        return 0;
    qsort(set1.data, set1.size, sizeof(int), compare_ints);
    qsort(set2.data, set2.size, sizeof(int), compare_ints);
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    assert(unordered_array_set_in(*set, value) < set->size);
    size_t posDeleteElement = unordered_array_set_in(*set, value);
    deleteByPosNotKeepingOrder(set->data, &set->size, posDeleteElement);
}

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    for (size_t i = 0; i < set2.size; i++)
        if (unordered_array_set_in(set1, set2.data[i]) == set1.size)
            unordered_array_set_insert(&set1, set2.data[i]);
    return (unordered_array_set) set1;
}

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3 = set1;
    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(set2, set1.data[i]) == set1.size)
            unordered_array_set_deleteElement(&set3, set1.data[i]);
    return set3;
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3 = set1;
    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(set2, set1.data[i]) != set1.size)
            unordered_array_set_deleteElement(&set3, set1.data[i]);
    return set3;
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3 = unordered_array_set_create(set1.capacity);
    for (size_t i = 0; i < set1.size; i++)
        if (unordered_array_set_in(set2, set1.data[i]) == set1.size)
            unordered_array_set_insert(&set3, set1.data[i]);
    for (size_t i = 0; i < set2.size; i++)
        if (unordered_array_set_in(set1, set2.data[i]) == set2.size)
            unordered_array_set_insert(&set3, set2.data[i]);
    return set3;
}

unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    unordered_array_set notSet = unordered_array_set_difference(universumSet, set);
    return notSet;
}

void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
}

bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (size_t i = 0; i < subset.size; i++)
        if (linearSearch(set.data, set.size, subset.data[i]) == set.size)
            return false;
    return true;
}

