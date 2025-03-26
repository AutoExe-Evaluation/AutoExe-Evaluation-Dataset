#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void strange_sort_list(int *lst, int size, int **result, int *result_size) {
    *result = (int *)malloc(size * sizeof(int));
    int *temp_lst = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        temp_lst[i] = lst[i];
    }

    bool switcher = true;
    int count = 0;

    while (size > 0) {
        int index = 0;
        for (int i = 1; i < size; i++) {
            if ((switcher && temp_lst[i] < temp_lst[index]) || (!switcher && temp_lst[i] > temp_lst[index])) {
                index = i;
            }
        }

        (*result)[count++] = temp_lst[index];

        for (int i = index; i < size - 1; i++) {
            temp_lst[i] = temp_lst[i + 1];
        }
        size--;
        switcher = !switcher;
    }

    *result_size = count;
    free(temp_lst);
}