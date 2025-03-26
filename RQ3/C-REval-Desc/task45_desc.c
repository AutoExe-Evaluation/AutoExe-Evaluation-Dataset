#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(int *arr, int size);

int has_only_odd_digits(int num) {
    while (num > 0) {
        if ((num % 10) % 2 == 0) {
            return 0;
        }
        num /= 10;
    }
    return 1;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b;
}

void unique_digits(int *x, int size) {
    int *odd_digit_elements = (int *)malloc(size * sizeof(int));
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (has_only_odd_digits(x[i])) {
            odd_digit_elements[count++] = x[i];
        }
    }

    qsort(odd_digit_elements, count, sizeof(int), compare);
    
    assert(func(odd_digit_elements, count));

    free(odd_digit_elements);
}