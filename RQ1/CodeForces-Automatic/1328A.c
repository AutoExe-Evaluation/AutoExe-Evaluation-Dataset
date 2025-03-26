#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within the range

    while (TC--) {
        int x, y;
        scanf("%d%d", &x, &y);
        assert(x >= 1 && x <= 1000000000); // PRE: a is within the range
        assert(y >= 1 && y <= 1000000000); // PRE: b is within the range
        
        int moves = (x % y) ? (y - (x % y)) : 0;
        printf("%d\n", moves);
        
        assert(moves >= 0); // POST: The number of moves cannot be negative
    }
    return 0;
}