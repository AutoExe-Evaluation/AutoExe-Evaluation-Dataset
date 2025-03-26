#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
} Pair;

int count_occurrences(char *arr[], int size, char *str) {
    int count = 0;
    for (int j = 0; j < size; j++) {
        if (strcmp(arr[j], str) == 0) {
            count++;
        }
    }
    return count;
}

int func(Pair *arr, int size);

void histogram(char *test) {
    Pair dict1[50];
    int list1_size = 0;
    char *list1[50];
    char *token = strtok(test, " ");
    int t = 0;

    while (token != NULL) {
        list1[list1_size++] = token;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < list1_size; i++) {
        int count = count_occurrences(list1, list1_size, list1[i]);
        if (count > t && strcmp(list1[i], "") != 0) {
            t = count;
        }
    }

    int dict_size = 0;
    if (t > 0) {
        for (int i = 0; i < list1_size; i++) {
            if (count_occurrences(list1, list1_size, list1[i]) == t) {
                strcpy(dict1[dict_size].key, list1[i]);
                dict1[dict_size].value = t;
                dict_size++;
            }
        }
    }

    assert(func(dict1, dict_size));
}