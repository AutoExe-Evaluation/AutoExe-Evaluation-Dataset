#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool good(int *v, int n, int del) {
    for (int i = del; i < n - 1; ++i) {
        if (i == del) continue;
        int last = gcd(v[i], v[i + 1]);
        if (i > del && last < gcd(v[i - 1], v[i])) {
            return false;
        }
        if (i < n - 2 && last < gcd(v[i + 1], v[i + 2])) {
            return false;
        }
    }
    return true;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases must be between 1 and 10^4
    for (int TC = 0; TC < TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 200000); // PRE: Size of array a must be between 3 and 2*10^5
        int *v = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= 1000000000); // PRE: Elements of array a must be positive integers
        }
        int del = -1;
        long long last = gcd(v[0], v[1]);
        for (int i = 1; i < n - 1; ++i) {
            long long cur = gcd(v[i], v[i + 1]);
            if (cur < last) {
                del = i;
                break;
            }
            last = cur;
        }
        if (del == -1 || good(v, n, del - 1) || good(v, n, del) || good(v, n, del + 1)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        free(v);
    }
    return 0; 
} // POST: Outputs "YES" or "NO" based on the conditions for staying non-decreasing in the GCD-sequence.