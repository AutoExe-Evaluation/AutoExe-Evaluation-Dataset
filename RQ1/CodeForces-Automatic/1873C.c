#include <stdio.h>
#include <assert.h>

int main() {
    // PRE: The input consists of valid test cases with the expected format.
    int t = 0;
    scanf("%d", &t);
    assert(t >= 1 && t <= 1000); // PRE: 1 <= t <= 1000

    while (t--) {
        char v[10][11];
        for (int i = 0; i < 10; ++i) {
            scanf("%s", v[i]);
        }
        int points = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (v[i][j] == 'X') {
                    int min_dist = i < j ? (i < (9 - j) ? i : (9 - j)) : (j < (9 - i) ? j : (9 - i));
                    points += min_dist + 1;
                }
            }
        }
        printf("%d\n", points);
        assert(points >= 0); // POST: points should be non-negative
    }
    return 0;
}