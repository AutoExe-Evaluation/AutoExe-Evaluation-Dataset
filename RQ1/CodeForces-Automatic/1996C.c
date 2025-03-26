#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXN 200000
#define ALPHABET_SIZE 26

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: 1 ≤ T <= 1000

    while (TCS--) {
        int n, q;
        scanf("%d %d", &n, &q);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 200000
        assert(q >= 1 && q <= 200000); // PRE: 1 ≤ q ≤ 200000
        
        char a[MAXN + 1], b[MAXN + 1];
        scanf("%s %s", a, b);
        assert(strlen(a) == n && strlen(b) == n); // PRE: Length.assertion

        long long cnt[ALPHABET_SIZE] = {0};
        long long v[MAXN + 1][ALPHABET_SIZE] = {0};

        for (int i = 0; i < n; i++) {
            cnt[a[i] - 'a']++;
            cnt[b[i] - 'a']--;
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                v[i + 1][j] = cnt[j];
            }
        }

        while (q--) {
            int l, r;
            scanf("%d %d", &l, &r);
            assert(1 <= l && l <= r && r <= n); // PRE: 1 ≤ l ≤ r ≤ n

            long long op = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                op += abs(v[l - 1][i] - v[r][i]);
            }
            printf("%lld\n", op / 2);
            assert(op / 2 >= 0); // POST: Operations should be ≥ 0
        }
    }
    return 0;
}