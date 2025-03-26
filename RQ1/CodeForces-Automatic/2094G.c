#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4

    while (TCS--) {
        ll q;
        scanf("%lld", &q);
        assert(q >= 1 && q <= 200000); // PRE: 1 <= q <= 2 * 10^5
        ll *d = (ll *)malloc(q * sizeof(ll));
        ll *rd = (ll *)malloc(q * sizeof(ll));
        ll riz = 0, r_riz = 0, tot = 0, n = 0, front_d = 0, back_d = -1, front_rd = 0, back_rd = -1;

        while (q--) {
            ll s;
            scanf("%lld", &s);
            assert(s >= 1 && s <= 3); // PRE: 1 <= s <= 3
            
            if (s == 1) {
                assert(back_d >= 0); // Ensuring there's an element to cyclic shift
                ll k = d[back_d--];
                if (back_d < 0) {
                    back_d = front_d - 1;
                }
                front_d++;
                d[front_d] = k;

                riz -= n * k;
                riz += k;
                riz += (tot - k);

                k = rd[front_rd++];
                r_riz -= k;
                r_riz += n * k;
                r_riz -= (tot - k);
            } else if (s == 2) {
                ll temp = riz;
                riz = r_riz;
                r_riz = temp;

                ll *temp_arr = d;
                d = rd;
                rd = temp_arr;

                ll temp_front = front_d;
                front_d = front_rd;
                front_rd = temp_front;

                ll temp_back = back_d;
                back_d = back_rd;
                back_rd = temp_back;
            } else {
                n++;
                ll k;
                scanf("%lld", &k);
                assert(k >= 1 && k <= 1000000); // PRE: 1 <= k <= 10^6
                tot += k;

                back_d++;
                d[back_d] = k;
                riz += n * k;

                front_rd--;
                rd[front_rd] = k;
                r_riz += k;
                r_riz += (tot - k);
            }
            printf("%lld\n", riz);
        }
        free(d);
        free(rd);
    }
    assert(riz == tot); // POST: The final rizziness equals the total sum after all operations
    return 0;
}