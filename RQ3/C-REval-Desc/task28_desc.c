#include <stdio.h>
#include <stdlib.h>

int* pluck(int* arr, int length) {
    int* _result = NULL;
    if (length == 0) {
        return _result;
    }
    
    int min_even = -1;
    int min_index = -1;
    
    for (int i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            if (min_even == -1 || arr[i] < min_even) {
                min_even = arr[i];
                min_index = i;
            }
        }
    }
    
    if (min_index == -1) {
        return _result;
    }
    
    _result = malloc(2 * sizeof(int));
    _result[0] = min_even;
    _result[1] = min_index;

    // assert(func(_result)); // POST condition to be verified externally

    return _result;
}