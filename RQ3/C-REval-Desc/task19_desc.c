#include <stdio.h>
#include <stdlib.h>

double func(double value);

double median(int* l, int size) {
    // Sort the array
    int* sorted_l = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        sorted_l[i] = l[i];
    }
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(sorted_l[j] > sorted_l[j + 1]) {
                int temp = sorted_l[j];
                sorted_l[j] = sorted_l[j + 1];
                sorted_l[j + 1] = temp;
            }
        }
    }

    double _result;
    if(size % 2 == 1) {
        _result = sorted_l[size / 2];
    } else {
        _result = (sorted_l[size / 2 - 1] + sorted_l[size / 2]) / 2.0;
    }

    free(sorted_l);
    assert(func(_result));
    return _result;
}