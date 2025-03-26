#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

long long min_cost(long long n, char *s) {
    long long ans = 0;
    long long *free = (long long *)malloc(n * sizeof(long long));
    long long *pay = (long long *)malloc(n * sizeof(long long));
    long long free_size = 0, pay_size = 0;

    assert(n > 0); // PRE: n should be greater than 0
    for (int i = 0; i < n; ++i) {
        ans += i + 1;
        if (s[i] == '0') {
            pay[pay_size++] = i + 1;
        } else {
            if (pay_size > 0) {
                pay_size--;
                free[free_size++] = i + 1;
            } else if (free_size > 0) {
                pay[pay_size++] = free[0];
                for (int j = 0; j < free_size - 1; j++) {
                    free[j] = free[j + 1];
                }
                free_size--;
                free[free_size++] = i + 1;
            } else {
                pay[pay_size++] = i + 1;
            }
        }
    }
    
    for (int i = 0; i < free_size; i++) {
        ans -= free[i];
    }

    free(free);
    free(pay);
    
    assert(ans >= 0); // POST: total cost must not be negative
    return ans;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS > 0); // PRE: Number of test cases should be greater than 0
    while (TCS--) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 400000); // PRE: n is within defined limits
        char *s = (char *)malloc((n + 1) * sizeof(char));
        scanf("%s", s);
        printf("%lld\n", min_cost(n, s));
        free(s);
    }
    return 0;
}