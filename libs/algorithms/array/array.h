#ifndef UNTITLED1_ARRAY_H
#define UNTITLED1_ARRAY_H

#include <stddef.h>

// ввод массива a размера n
void inputArray(int *a, size_t n);

// вывод массива a размера n
void outputArray(const int *a, size_t n);

/*возвращает индекс первого элемента в массиве a размера n, равного x,
если такого нет, то n */
size_t linearSearch(const int *a, size_t n, int x);

// возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе -1
size_t binarySearch(const int *a, size_t n, int x);

// возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает -1
size_t binarySearchMoreOrEqual(const int *a, size_t n, int x);

// вставка элемента со значением x
// в массив data размера n на позицию pos
void insert(int *a, size_t *n, size_t pos, int x);

// добавление элемента x в конец массива data размера n
void append(int *a, size_t *n, int x);

// удаление из массива a размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder(int *a, size_t *n, size_t pos);

// удаление из массива a размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// размер массива a уменьшается на единицу
void deleteByPosNotKeepingOrder(int *a, size_t *n, size_t pos);

// возвращает значение ’истина’ если все элементы
// массива a размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int all(const int *a, size_t n, int (*f)(int));

// возвращает значение ’истина’ если хотя бы один элемент
// массива a размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int any(const int *a, size_t n, int (*f)(int));

//применяет функцию f ко всем элементам массива a размера n
void forEach(int *a, size_t n, int (*f)(int));

// возвращает количество элементов массива a размера n, удовлетворяющих функции-предикату f
int getCountOfElementsIf(const int *a, size_t n, int (*f)(int));

// удаляет все элементы из массива a размера n, удовлетворяющие функции-предикату f
void deleteIf(int *a, size_t *n, int (*f)(int));

int getFirstNegativeIndex(const int *a, size_t n);

//возвращает индекс последнего четного элемента массива a размера n
int getLastEvenIndex(const int *a, size_t n);


/* возвращает индекс последнего элемента массива a размера n,
удовлетворяющего функции-предикату f */
int getLastIndexOfElementIf(const int *a, size_t n, int (*f)(int));

// возвращает количество отрицательных элементов массива a размера n
int countOfNegativeElements(const int *a, size_t n);

// производит обмен переменных a и b
void swap(int *a, int *b);

// изменяет порядок элементов массива a размера n на обратный
void reverseArray(int *a, size_t n);

//возвращает 1, если массив a размера n является палиндромом, иначе, 0
int isPalindrome(const int *a, size_t n);

// возвращает 1, если x больше y, иначе 0
int isDecreasing(int x, int y);

// возвращает 1, если x меньше y, иначе 0
int isIncreasing(int x, int y);

// сортирует массив a размера n по функции-предикату f
void selectionSort(int *a, size_t n, int (*f)(int, int));

//выполняет циклический сдвиг элементов массива a размера n на k
int cyclicShift(int *a, size_t n, size_t k);

//возвращает абсолютное значение x
int abs(int x);

/*разделяет массив a размера sizeA на два массива по принципу: если элемент
массива удовлетворяет функции-предикату f,
то записывается в массив b размера sizeB, иначе, в массив c размера sizeC */
void arraySplit(const int *a, size_t sizeA, int *b, size_t *sizeB, int
*c, size_t *sizeC, int (*f)(int));

// сортировка вставками
void insertionSort(int *a, size_t n);

#endif