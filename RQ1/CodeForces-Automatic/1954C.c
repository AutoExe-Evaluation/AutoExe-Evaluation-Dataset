#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--) {
        char x[102], y[102];
        scanf("%s %s", x, y);
        assert(strlen(x) == strlen(y)); // PRE: x and y have the same length

        int length = strlen(x);
        int f = 0;

        for (int i = 0; i < length; ++i) {
            if ((x[i] > y[i]) == f) {
                char temp = x[i];
                x[i] = y[i];
                y[i] = temp;
            }
            f |= (x[i] != y[i]);
        }
        
        printf("%s\n%s\n", x, y);
        // POST: The numbers x and y are maximized based on swapping rules
        assert(x[length - 1] >= '1' && y[length - 1] >= '1'); // Both x and y are valid integers after modifications
    }
    return 0;
}