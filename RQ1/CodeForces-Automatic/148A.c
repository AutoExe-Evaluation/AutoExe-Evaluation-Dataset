#include <stdio.h>
#include <assert.h>

int main() {
    int k, l, m, n, d;
    scanf("%d %d %d %d %d", &k, &l, &m, &n, &d);
    
    assert(k >= 1 && k <= 10); // PRE: k is between 1 and 10
    assert(l >= 1 && l <= 10); // PRE: l is between 1 and 10
    assert(m >= 1 && m <= 10); // PRE: m is between 1 and 10
    assert(n >= 1 && n <= 10); // PRE: n is between 1 and 10
    assert(d >= 1 && d <= 100000); // PRE: d is between 1 and 100000
    
    int damaged = 0;
    
    for (int i = 1; i <= d; i++) {
        if (i % k == 0 || i % l == 0 || i % m == 0 || i % n == 0) {
            damaged++;
        }
    }
    
    printf("%d\n", damaged);
    assert(damaged >= 0 && damaged <= d); // POST: damaged is between 0 and d
    
    return 0;
}