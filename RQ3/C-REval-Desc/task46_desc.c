#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* dic[] = {
    "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
};

void by_length(int* arr, int size, const char*** result, int* result_size) {
    int* sorted_arr = (int*)malloc(size * sizeof(int));
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= 1 && arr[i] <= 9) {
            sorted_arr[count++] = arr[i];
        }
    }

    qsort(sorted_arr, count, sizeof(int), (int (*)(const void*, const void*))cmp);

    char** new_arr = (char**)malloc(count * sizeof(char*));
    for (int i = count - 1; i >= 0; i--) {
        new_arr[count - 1 - i] = dic[sorted_arr[i]];
    }

    *result = new_arr;
    *result_size = count;

    free(sorted_arr);
}

int cmp(const int* a, const int* b) {
    return (*a > *b) - (*a < *b);
}

int func(const char** arr, int size); // Forward declaration for the assertion

int main() {
    int arr[] = {2, 1, 1, 4, 5, 8, 2, 3};
    const char** result;
    int result_size;

    by_length(arr, sizeof(arr) / sizeof(arr[0]), &result, &result_size);

    assert(func(result, result_size));

    free(result);
    return 0;
}