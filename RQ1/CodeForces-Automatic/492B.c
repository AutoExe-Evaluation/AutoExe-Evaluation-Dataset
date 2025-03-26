#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main() {
    int n, l;
    scanf("%d %d", &n, &l);
    
    assert(n >= 1 && n <= 1000); // PRE: n is within the bounds
    assert(l >= 1 && l <= 1000000000); // PRE: l is within the bounds

    int *lamps = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &lamps[i]);

    int mx = 0;
    qsort(lamps, n, sizeof(int), (__compar_fn_t) strcmp);

    for (int i = 1; i < n; ++i) {
        int x = lamps[i] - lamps[i - 1];
        if (x > mx) mx = x;
    }

    double dis = fmax(lamps[0] - 0, l - lamps[n - 1]);
    double result = fmax(dis, (double)mx / 2);
    
    printf("%.10lf\n", result);

    assert(result >= 0); // POST: d is non-negative
    assert(result <= (double)l); // POST: d does not exceed the street length l

    free(lamps);
    return 0;
}