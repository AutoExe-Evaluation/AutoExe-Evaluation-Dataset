#include <stdio.h>
#include <stdlib.h>

int func(int* result, int size);

int* tri(int n) {
    int* my_tri = (int*)malloc((n + 1) * sizeof(int));
    if (n == 0) {
        my_tri[0] = 1;
    } else {
        my_tri[0] = 1;
        my_tri[1] = 3;
        for (int i = 2; i <= n; i++) {
            if (i % 2 == 0) {
                my_tri[i] = i / 2 + 1;
            } else {
                my_tri[i] = my_tri[i - 1] + my_tri[i - 2] + (i + 3) / 2;
            }
        }
    }
    int result = func(my_tri, n + 1);
    return my_tri;
}