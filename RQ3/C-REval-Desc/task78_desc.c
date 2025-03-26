#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int func(char *arr[], int size);

int compare(const void *a, const void *b) {
    char *strA = *(char **)a;
    char *strB = *(char **)b;
    int lenA = strlen(strA);
    int lenB = strlen(strB);
    if (lenA == lenB) {
        return strcmp(strA, strB);
    }
    return lenA - lenB;
}

int sorted_list_sum(char *lst[], int size) {
    qsort(lst, size, sizeof(char *), compare);
    char **new_lst = malloc(size * sizeof(char *));
    int new_size = 0;

    for (int i = 0; i < size; i++) {
        if (strlen(lst[i]) % 2 == 0) {
            new_lst[new_size++] = lst[i];
        }
    }

    qsort(new_lst, new_size, sizeof(char *), compare);
    int result = func(new_lst, new_size);
    free(new_lst);
    return result;
}