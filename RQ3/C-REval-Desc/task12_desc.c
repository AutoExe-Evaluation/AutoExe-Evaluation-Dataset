#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* factorize(int n, int* size) {
    int* fact = malloc(100 * sizeof(int)); // Assume a max size of 100 for simplicity
    int i = 2;
    *size = 0;

    while (i <= (int)(sqrt(n) + 1)) {
        if (n % i == 0) {
            fact[(*size)++] = i;
            n /= i;
        } else {
            i++;
        }
    }

    if (n > 1) {
        fact[(*size)++] = n;
    }
    
    // Here is where you would usually call func(fact, *size) for assertion
    return fact;
}