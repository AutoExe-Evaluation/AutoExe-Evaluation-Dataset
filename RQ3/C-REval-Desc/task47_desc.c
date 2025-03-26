#include <stdio.h>
#include <stdlib.h>

int func(int *arr, int size);

int* f(int n) {
    int *ret = (int*)malloc(n * sizeof(int));
    for (int i = 1; i <= n; i++) {
        int x;
        if (i % 2 == 0) {
            x = 1;
            for (int j = 1; j <= i; j++) {
                x *= j;
            }
        } else {
            x = 0;
            for (int j = 1; j <= i; j++) {
                x += j;
            }
        }
        ret[i - 1] = x;
    }
    int _result_size = n;

    assert(func(ret, _result_size)); // POST: func is equivalent to: Implement the function f that takes n as a parameter, and returns a list of size n, such that the value of the element at index i is the factorial of i if i is even or the sum of numbers i starts the factorial of i is the multiplication of the numbers Example: f(5) == [1, 2, 6, 24, 15] 
    return ret;
}