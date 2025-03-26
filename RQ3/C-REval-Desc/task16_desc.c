#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int func(int x);

void prime_fib(int n) {
    int f[1000] = {0, 1};
    int index = 2;

    while (true) {
        f[index] = f[index - 1] + f[index - 2];
        bool is_prime = true;

        if (f[index] < 2) {
            is_prime = false;
        }

        for (int k = 2; k <= fmax((int)sqrt(f[index]), f[index] - 1); k++) {
            if (f[index] % k == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            n -= 1;
        }

        if (n == 0) {
            int _result = f[index];
            if (!func(_result)) {
                return;
            }
        }
        
        index++;
    }
}