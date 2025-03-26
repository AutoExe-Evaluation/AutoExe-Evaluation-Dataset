#include <stdio.h>
#include <stdlib.h>

int* rolling_max(int* numbers, int length) {
    int* result = (int*)malloc(length * sizeof(int));
    int running_max = -2147483648; // Initialize to the smallest int

    for (int i = 0; i < length; i++) {
        if (i == 0) {
            running_max = numbers[i];
        } else {
            if (running_max < numbers[i]) {
                running_max = numbers[i];
            }
        }
        result[i] = running_max;
    }

    return result;
}