#include <stdio.h>
#include <assert.h>

int main() {
    long long n, a, b;
    scanf("%lld%lld%lld", &n, &a, &b);
    assert(n >= 1 && n <= 100); // PRE: n must be between 1 and 100
    assert(a >= 1 && a <= n); // PRE: a must be between 1 and n
    assert(b >= 1 && b <= n); // PRE: b must be between 1 and n

    int v[101] = {0};

    for (int i = 0; i < a; ++i) {
        long long x;
        scanf("%lld", &x);
        assert(x >= 1 && x <= n); // PRE: Apples liked by Arthur must be within 1 to n
        v[x] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        if (v[i] == 0)
            printf("2 ");
        else
            printf("1 ");
    }

    // POST: Each apple is either assigned to 1 (Arthur) or 2 (Alexander)
    assert(1 <= n && n <= 100); // POST: Output must have n characters (1 or 2)
    
    return 0;
}