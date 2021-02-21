/***************************************************************************/
/* Функция быстрой сортировки                                              */
/* Алгоритм выполняется в лучшем/среднем случаем по времени за O(n*log(n)) */
/* Quick sort function                                                     */
/* The algorithm runs at best / average time in O(n * log(n))              */
/***************************************************************************/

#include <cstdlib>
#include <iostream>

void quickSortIter(int* array, long size) {
    if (!isSorted(array, size)) {
        long i;                                 // Pointers for iterations. Указатели для итераций
        long j;
        long lb;                                // Left border. Левая граница
        long rb;                                // Right border. Правая граница

        long maxBuffSize = size / 2 + 1;
        long* lbstack = new long[maxBuffSize];  // Request stack for left bounds. Стек запросов для левых границ
        long* rbstack = new long[maxBuffSize];  // Request stack for right bounds. Стек запросов для правых границ

        long stackpos = 1;                      // Current stack position. Текущая позиция стека
        long median;                            // Middle of array. Середина массива
        int pivot;                              // Pivot element. Опорный элемент
        int temp;                               // Variable to swap values. Переменная для перестановки значений.

        lbstack[1] = 0;
        rbstack[1] = size - 1;

        do {
            // Pop the lb and rb boundaries of the current array from the stack.
            // Берем границы lb and rb текущего массива из стека.
            lb = lbstack[stackpos];
            rb = rbstack[stackpos];
            stackpos--;

            do {
                median = (lb + rb) >> 1;        // Find median. Находим середину текущего массива.
                i = lb;
                j = rb;
                pivot = array[median];              // Pick median as pivot. Выбираем серединный элемент как опорный.
                do {
                    while (array[i] < pivot) i++;
                    while (pivot < array[j]) j--;
                    if (i <= j) {
                        temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                        i++; j--;
                    }
                } while (i <= j);

                // Now the pointer i points to the beginning of the right subarray, j points to the end of the left
                // Сейчас указатель i указывает на начало правого подмассива, j указывает на конец левого

                // Push the indices of most of the array onto the stack and move the boundaries
                // Отправляем индексы большей части массива в стек и двигаем границы
                if (i < median) {               // The right side is larger. Правая часть больше
                    if (i < rb) {               // If it contains more than 1 element - need to sort, the request is pushed into the stack
                        stackpos++;             // Если он содержит более 1 элемента - нужно отсортировать, запрос помещается в стек
                        lbstack[stackpos] = i;
                        rbstack[stackpos] = rb;
                    }
                    rb = j;                     // Next iteration - work with the left side
                                                // Следующая итерация - работа с левой стороной
                }
                else {                          // The left side is larger. Левая часть больше
                    if (j > lb) {
                        stackpos++;
                        lbstack[stackpos] = lb;
                        rbstack[stackpos] = j;
                    }
                    lb = i;
                }
            } while (lb < rb);                  // While the smaller part contains more than 1 element
                                                // Пока в меньшей части более 1 элемента
        } while (stackpos != 0);                // While there are requests on the stack
                                                // Пока есть запросы в стеке
    }
}

void inputArray(int *array, size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        array[i] = std::rand()%100;
    }
    for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

bool isSorted(int* array, size_t size) {
    for (size_t i = 0; i < size-1; i++) {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
}

int main()
{
    const long size = 10;
    int array[size];

    inputArray(array, size);

    quickSortIter(array, size);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}