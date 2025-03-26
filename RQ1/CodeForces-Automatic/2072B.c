#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ll long long

void solve(int n, char* s) {
    int d = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '-') 
            d++;
    }
    int u = n - d;
    assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2*10^5
    assert(d >= 0 && u >= 0); // PRE: d and u must be non-negative
    if (n < 3 || d < 2 || u < 1) {
        printf("0\n");
        return;
    }
    int x = d / 2;
    int y = d - x;
    ll result = x * (ll)u * y;
    assert(result >= 0); // POST: result should be non-negative
    printf("%lld\n", result);
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= TCS <= 10^4
    for (int TC = 1; TC <= TCS; TC++) {
        int n;
        char s[200001];
        scanf("%d %s", &n, s);
        solve(n, s);
    }
    return 0;
}