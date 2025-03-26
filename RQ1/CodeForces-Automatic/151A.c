#include <stdio.h>
#include <assert.h>

#define min(a, b, c) ((a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c))

int main() {
    int n, k, l, c, d, p, nl, np;
    scanf("%d %d %d %d %d %d %d %d", &n, &k, &l, &c, &d, &p, &nl, &np);

    // PRE: n > 0 && k > 0 && l > 0 && c > 0 && d > 0 && p > 0 && nl > 0 && np > 0
    assert(n > 0 && k > 0 && l > 0 && c > 0 && d > 0 && p > 0 && nl > 0 && np > 0);

    int drink = (k * l) / nl;
    int slices = c * d;
    int salt = p / np;
    int toast = min(drink, slices, salt);

    printf("%d\n", toast / n);

    // POST: The result is non-negative and represents the number of toasts each friend can make
    assert(toast / n >= 0); // Ensure the output is valid
    return 0;
}