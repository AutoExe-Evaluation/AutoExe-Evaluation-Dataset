#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 100

int main() {
    long long n, m;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100
    int a[MAX];
    for (long long i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        assert(a[i] >= 1 && a[i] <= 100); // PRE: 1 ≤ a[i] ≤ 100
    }
    
    scanf("%lld", &m);
    assert(m >= 1 && m <= 100); // PRE: 1 ≤ m ≤ 100
    int b[MAX];
    for (long long i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        assert(b[i] >= 1 && b[i] <= 100); // PRE: 1 ≤ b[i] ≤ 100
    }
    
    // Sort arrays a and b
    for (long long i = 0; i < n - 1; i++) {
        for (long long j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    
    for (long long i = 0; i < m - 1; i++) {
        for (long long j = 0; j < m - i - 1; j++) {
            if (b[j] > b[j + 1]) {
                int temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
    
    long long ct = 0;
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            int dif = abs(a[i] - b[j]);
            if (dif < 2) {
                b[j] = 1000;
                ct++;
                break;
            }
        }
    }
    
    printf("%lld\n", ct);
    assert(ct >= 0 && ct <= n && ct <= m); // POST: 0 ≤ ct ≤ min(n, m)
    
    return 0;
}