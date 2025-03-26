#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ll long long

ll pow(ll x, ll y, ll m) {
    ll ans = 1;
    x %= m;
    while(y) {
        if(y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

void Zfunc(char *str, int n, int *z) {
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i <= r) z[i] = (r - i + 1 < z[i - l]) ? r - i + 1 : z[i - l];
        while(i + z[i] < n && str[z[i]] == str[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10000

    for(int TC = 1; TC <= TCS; ++TC) {
        int n, k;
        scanf("%d %d %d", &n, &k, &k);
        
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 200000
        assert(k == k); // PRE: l = r → k = k

        char *s = (char *)malloc((n + 1) * sizeof(char));
        scanf("%s", s);
        
        assert(strlen(s) == n); // PRE: Length of s should be n

        int *z = (int *)calloc(n, sizeof(int));
        Zfunc(s, n, z);

        ll low = 1, high = n, ans = 0;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            ll cnt = 1;
            for(int i = mid; i < n;) {
                if(z[i] >= mid) {
                    cnt++;
                    i += mid;
                } else {
                    i++;
                }
            }
            if(cnt >= k) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("%lld\n", ans);

        free(s);
        free(z);

        assert(ans >= 0 && ans <= n); // POST: ans should be within valid range
    }
    return 0;
}