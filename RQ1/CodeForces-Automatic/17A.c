#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 1000

bool is_prime[1001];

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    
    assert(n >= 2 && n <= 1000); // PRE: 2 ≤ n ≤ 1000
    assert(k >= 0 && k <= 1000); // PRE: 0 ≤ k ≤ 1000

    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; ++i) {
        is_prime[i] = true;
    }

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int v[1001], idx = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime[i]) {
            v[idx++] = i;
        }
    }

    int ct = 0;
    for (int i = 0; i < idx; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (v[j] + v[j - 1] == v[i] - 1) {
                ct++;
                break;
            }
        }
        if (ct >= k) {
            printf("YES\n");
            assert(ct >= k); // POST: At least k primes can be expressed as described
            return 0;
        }
    }
    printf("NO\n");
    assert(ct < k); // POST: Less than k primes can be expressed as described
    return 0;
}