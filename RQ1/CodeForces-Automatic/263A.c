#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int i, j, value, move, x, y;
    int oneFound = 0;

    for(i = 1; i <= 5; i++) {
        for(j = 1; j <= 5; j++) {
            scanf("%d", &value);
            if(value == 1) {
                x = i;
                y = j;
                oneFound = 1;
                break;
            }
        }
        if(oneFound) break;
    }

    assert(oneFound == 1); // PRE: A single number 1 must be present in the matrix.
    move = abs(x - 3) + abs(y - 3);
    printf("%d\n", move);
    assert(move >= 0); // POST: The number of moves must be non-negative.
    return 0;
}