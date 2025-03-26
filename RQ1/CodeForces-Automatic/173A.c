#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
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

    int n, m, k;
    char s1[1002], s2[1002];
    scanf("%d %s %s", &n, s1, s2);
    m = strlen(s1);
    k = strlen(s2);
    
    // PRE: n should be at least 1, m and k should be at least 1
    assert(n >= 1 && m >= 1 && k >= 1);

    int l = m / __gcd(m, k) * k;
    char str1[2002] = {0}, str2[2002] = {0};
    strcpy(str1, s1);
    strcpy(str2, s2);
    for (int i = 0; i <= l / m; i++) strcat(str1, s1);
    for (int i = 0; i <= l / k; i++) strcat(str2, s2);
    int p = n / l;
    int q = n % l;
    long long ct1 = 0, ct2 = 0, ans1 = 0, ans2 = 0;

    for (int i = 0; i < l && i < n; ++i) {
        char a = str1[i];
        char b = str2[i];
        if (a == 'R') {
            if (b == 'P') ct1++;
            else if (b == 'S') ct2++;
        } else if (a == 'P') {
            if (b == 'R') ct2++;
            else if (b == 'S') ct1++;
        } else if (a == 'S') {
            if (b == 'R') ct1++;
            else if (b == 'P') ct2++;
        }
        if (i == q - 1) {
            ans1 = ct1;
            ans2 = ct2;
        }
    }
    
    // POST: The total red spots for both players after n rounds are calculated correctly
    printf("%lld %lld\n", p * ct1 + ans1, p * ct2 + ans2);
    assert((p * ct1 + ans1 >= 0) && (p * ct2 + ans2 >= 0));

    return 0;
}