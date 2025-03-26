#include <stdio.h>
#include <assert.h>

int main() {
    long long a, b, c, TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 100000); // PRE: 1 ≤ TC ≤ 100000

    while (TC--) {
        scanf("%lld %lld %lld", &a, &b, &c);
        assert(a >= 1 && a <= 100); // PRE: 1 ≤ a ≤ 100
        assert(b >= 1 && b <= 100); // PRE: 1 ≤ b ≤ 100
        assert(c >= 1 && c <= 100); // PRE: 1 ≤ c ≤ 100

        int v[3] = {0};
        long long x = a, y = b, z = c, tmp;

        tmp = (y < z) ? y : z;
        y -= tmp;
        z -= tmp;
        x += tmp;
        if (x > 0 && (y > z ? y : z) % 2 == 0)
            v[0] = 1;

        x = a, y = b, z = c;
        tmp = (x < z) ? x : z;
        x -= tmp;
        z -= tmp;
        y += tmp;
        if (y > 0 && (x > z ? x : z) % 2 == 0)
            v[1] = 1;

        x = a, y = b, z = c;
        tmp = (x < y) ? x : y;
        x -= tmp;
        y -= tmp;
        z += tmp;
        if (z > 0 && (x > y ? x : y) % 2 == 0)
            v[2] = 1;

        for (int i = 0; i < 3; i++)
            printf("%d ", v[i]);
        printf("\n");
        
        // POST: v[0], v[1], v[2] are correctly calculated based on given a, b, c.
    }
    return 0;
}