#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool func(int* arr, int size);

int* count_up_to(int n, int* size) {
    int* primes = malloc(n * sizeof(int));
    *size = 0;

    for (int i = 2; i < n; i++) {
        bool is_prime = true;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes[*size] = i;
            (*size)++;
        }
    }

    int* result = realloc(primes, (*size) * sizeof(int));
    assert(func(result, *size));
    return result;
}