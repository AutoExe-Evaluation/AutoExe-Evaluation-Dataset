#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int ll;

int main() {
    int TC;
    scanf("%d", &TC);
    
    assert(TC >= 1 && TC <= 1000); // PRE: 1 <= t <= 1000
    
    while (TC--) {
        ll a, b, k1, k2, q1, q2;
        scanf("%lld %lld", &a, &b);
        scanf("%lld %lld", &k1, &k2);
        scanf("%lld %lld", &q1, &q2);

        assert(a >= 1 && a <= 100000000 && b >= 1 && b <= 100000000); // PRE: 1 <= a, b <= 10^8
        assert(k1 >= 0 && k1 <= 100000000 && k2 >= 0 && k2 <= 100000000); // PRE: 0 <= x_K, y_K <= 10^8
        assert(q1 >= 0 && q1 <= 100000000 && q2 >= 0 && q2 <= 100000000); // PRE: 0 <= x_Q, y_Q <= 10^8
        assert(!(k1 == q1 && k2 == q2)); // PRE: (x_K, y_K) != (x_Q, y_Q)

        ll k[8][2], q[8][2];
        int ct = 0;

        k[0][0] = k1 + a; k[0][1] = k2 + b;
        k[1][0] = k1 + a; k[1][1] = k2 - b;
        k[2][0] = k1 - a; k[2][1] = k2 + b;
        k[3][0] = k1 - a; k[3][1] = k2 - b;
        k[4][0] = k1 + b; k[4][1] = k2 + a;
        k[5][0] = k1 + b; k[5][1] = k2 - a;
        k[6][0] = k1 - b; k[6][1] = k2 + a;
        k[7][0] = k1 - b; k[7][1] = k2 - a;

        q[0][0] = q1 + a; q[0][1] = q2 + b;
        q[1][0] = q1 + a; q[1][1] = q2 - b;
        q[2][0] = q1 - a; q[2][1] = q2 + b;
        q[3][0] = q1 - a; q[3][1] = q2 - b;
        q[4][0] = q1 + b; q[4][1] = q2 + a;
        q[5][0] = q1 + b; q[5][1] = q2 - a;
        q[6][0] = q1 - b; q[6][1] = q2 + a;
        q[7][0] = q1 - b; q[7][1] = q2 - a;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (k[i][0] == q[j][0] && k[i][1] == q[j][1]) {
                    ct++;
                }
            }
        }

        printf("%lld\n", ct);
        assert(ct >= 0); // POST: ct >= 0
    }
    return 0;
}