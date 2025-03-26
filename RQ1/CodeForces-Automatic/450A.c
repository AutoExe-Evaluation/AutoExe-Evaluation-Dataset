#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    long long first;
    long long second;
} pair;

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    assert(n >= 1 && n <= 100); // PRE: n is within the bounds
    assert(m >= 1 && m <= 100); // PRE: m is within the bounds
    
    pair *q = (pair *)malloc(n * sizeof(pair));
    long long front = 0, back = 0;

    for (long long i = 1; i <= n; ++i) {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= 100); // PRE: a[i] is within the bounds
        q[back].first = x;
        q[back].second = i;
        back++;
    }
    
    long long x, i = 0;
    while (front < back) {
        x = q[front].first;
        i = q[front].second;
        front++;
        if (x > m) {
            q[back].first = x - m;
            q[back].second = i;
            back++;
        }
    }
    printf("%lld\n", i);
    
    assert(i >= 1 && i <= n); // POST: last child's index is within the bounds
    free(q);
    return 0;
}
