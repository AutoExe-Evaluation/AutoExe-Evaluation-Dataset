#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 200000

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases t is within the bounds
    for (int TC = 1; TC <= TCS; TC++) {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of the array n is within the bounds
        ll a[MAX_N];
        ll *pointers[1000000] = { NULL };
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 0 && a[i] <= 1000000000); // PRE: Each element a_i is nonnegative and within the bounds
            ll index = a[i] >> 2;
            if (pointers[index] == NULL) {
                pointers[index] = (ll *)malloc(n * sizeof(ll));
                memset(pointers[index], 0, n * sizeof(ll));
            }
            pointers[index][(ll)pointers[index][0] + 1] = -a[i];
            pointers[index][0]++;
        }
        for (int i = 0; i < n; i++) {
            ll index = a[i] >> 2;
            ll max_elem = -pointers[index][1];
            printf("%lld ", max_elem);
            pointers[index][1] = pointers[index][pointers[index][0]];
            pointers[index][0]--;
        }
        printf("\n");
        // POST: The output array is lexicographically smallest
    }
    return 0;
}