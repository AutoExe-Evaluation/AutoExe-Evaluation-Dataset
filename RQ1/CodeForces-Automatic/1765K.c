#include <stdio.h>
#include <limits.h>
#include <assert.h>

typedef long long ll;

int main() {
    ll n;
    scanf("%lld", &n);
    
    // PRE: The grid size n should be at least 2 and at most 200
    assert(n >= 2 && n <= 200);
    
    ll grid[200][200];
    ll sum = 0, mn = LONG_MAX;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            scanf("%lld", &grid[i][j]);
            sum += grid[i][j];
        }
        if (grid[i][n - 1 - i] < mn) {
            mn = grid[i][n - 1 - i];
        }
    }
    
    // POST: The result should be the sum of visited cells minus the minimum cell in the diagonal
    assert(sum - mn >= 0); // The score cannot be negative

    printf("%lld\n", sum - mn);
    return 0;
}