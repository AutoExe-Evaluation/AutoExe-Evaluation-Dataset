#include <stdio.h>
#include <stdlib.h>

int func(int* arr, int size);

void common(int* l1, int size1, int* l2, int size2) {
    int* ret = (int*)malloc(size1 * sizeof(int));
    int ret_size = 0;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (l1[i] == l2[j]) {
                int found = 0;
                for (int k = 0; k < ret_size; k++) {
                    if (ret[k] == l1[i]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    ret[ret_size++] = l1[i];
                }
            }
        }
    }

    // Sort ret array
    for (int i = 0; i < ret_size - 1; i++) {
        for (int j = i + 1; j < ret_size; j++) {
            if (ret[i] > ret[j]) {
                int temp = ret[i];
                ret[i] = ret[j];
                ret[j] = temp;
            }
        }
    }

    assert(func(ret, ret_size));

    free(ret);
}