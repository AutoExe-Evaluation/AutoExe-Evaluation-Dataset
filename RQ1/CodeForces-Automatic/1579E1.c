#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 <= TCS <= 1000
    
    for (int TC = 1; TC <= TCS; ++TC) {
        ll n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        
        ll* d = (ll*)malloc(n * sizeof(ll));
        ll front = -1, back = 0;

        for (ll i = 0; i < n; ++i) {
            ll x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= n); // PRE: 1 <= p_i <= n
            
            if (front != -1 && d[front] > x) {
                front++;
                d[front] = x;
            } else {
                d[back++] = x;
            }
        }

        for (ll i = front; i >= 0; --i) {
            printf("%lld ", d[i]);
        }
        for (ll i = 0; i < back; ++i) {
            printf("%lld ", d[i]);
        }
        printf("\n");

        // POST: The printed sequence is the lexicographically smallest sequence possible.
        free(d);
    }
    return 0;
}