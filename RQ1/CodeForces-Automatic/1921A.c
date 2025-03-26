#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: 1 ≤ t ≤ 100

    while (TC--) {
        int v[4][2];
        for (int i = 0; i < 4; ++i) {
            scanf("%lld %lld", &v[i][0], &v[i][1]);
            assert(v[i][0] >= -1000 && v[i][0] <= 1000); // PRE: -1000 ≤ x_i ≤ 1000
            assert(v[i][1] >= -1000 && v[i][1] <= 1000); // PRE: -1000 ≤ y_i ≤ 1000
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (v[i][0] > v[j][0]) {
                    int temp0 = v[i][0];
                    int temp1 = v[i][1];
                    v[i][0] = v[j][0];
                    v[j][0] = temp0;
                    v[i][1] = v[j][1];
                    v[j][1] = temp1;
                }
            }
        }

        int diff = llabs(v[0][1] - v[1][1]);
        assert(diff > 0); // POST: The area is strictly greater than 0
        printf("%lld\n", diff * diff); // POST: Output the area of the square
    }
    return 0;
}