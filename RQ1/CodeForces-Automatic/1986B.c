#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within bounds.

    while (TCS--) {
        ll n, m;
        scanf("%lld %lld", &n, &m);
        assert(n >= 1 && n <= 100 && m >= 1 && m <= 100); // PRE: Matrix dimensions are within bounds.

        ll **v = (ll **)malloc(n * sizeof(ll *));
        for (ll i = 0; i < n; ++i) {
            v[i] = (ll *)malloc(m * sizeof(ll));
            for (ll j = 0; j < m; ++j) {
                scanf("%lld", &v[i][j]);
                assert(v[i][j] >= 1 && v[i][j] <= 1000000000); // PRE: Matrix values are within bounds.
            }
        }
        
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                ll mx = 0;
                if (i + 1 < n)  
                    mx = (mx > v[i + 1][j]) ? mx : v[i + 1][j];
                if (i - 1 >= 0)   
                    mx = (mx > v[i - 1][j]) ? mx : v[i - 1][j];
                if (j + 1 < m) 
                    mx = (mx > v[i][j + 1]) ? mx : v[i][j + 1];
                if (j - 1 >= 0)  
                    mx = (mx > v[i][j - 1]) ? mx : v[i][j - 1];
                if (v[i][j] > mx)  
                    v[i][j] = mx;
                assert(v[i][j] >= 0); // POST: No matrix value should be negative.
                printf("%lld ", v[i][j]);
            }
            printf("\n");
        }
        
        for (ll i = 0; i < n; ++i) {
            free(v[i]);
        }
        free(v);
    }
    return 0;
}