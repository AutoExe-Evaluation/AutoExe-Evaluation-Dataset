#include <stdio.h>
#include <stdlib.h>

int func(int result);

int search(int* lst, int size) {
    int max_val = 0;
    for (int j = 0; j < size; j++) {
        if (lst[j] > max_val) {
            max_val = lst[j];
        }
    }

    int* frq = (int*)calloc(max_val + 1, sizeof(int));
    for (int i = 0; i < size; i++) {
        frq[lst[i]]++;
    }

    int ans = -1;
    for (int i = 1; i <= max_val; i++) {
        if (frq[i] >= i) {
            ans = i;
        }
    }

    free(frq);

    int _result = ans;
    if (!func(_result)) {
        // Handle assertion failure if needed
    }
    return _result;
}