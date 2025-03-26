#include <stdio.h>
#include <assert.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

long long prod_of_three(long long a, long long b, long long c) {
    return a * b * c;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000

    while (TCS--) {
        long long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        assert(a >= 1 && a <= 10 && b >= 1 && b <= 10 && c >= 1 && c <= 10); // PRE: 1 <= a, b, c <= 10

        for (int i = 0; i < 5; ++i) {
            if (a <= b && a <= c) {
                a++;
            } else if (b <= a && b <= c) {
                b++;
            } else {
                c++;
            }
        }

        long long result = prod_of_three(a, b, c);
        printf("%lld\n", result);
        assert(result >= 1); // POST: result should be positive as a, b, c are >=1
    }
    return 0;
}