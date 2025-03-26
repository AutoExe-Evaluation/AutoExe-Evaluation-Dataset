#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: number of test cases is within bounds

    for (int TC = 1; TC <= TCS; ++TC) {
        int n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);
        
        assert(n >= 0 && m >= 0 && n + m >= 1 && n + m <= 200000); // PRE: n, m, and n + m are within bounds
        assert(k >= 1 && k <= n + m); // PRE: k is within bounds
        
        if (abs(n - m) > k || (n < k && m < k)) {
            printf("-1\n");
            continue;
        }
        
        int x = n / k;
        int y = m / k;
        int ex = n % k;
        int ey = m % k;
        int mx = (x > y) ? x : y;
        int mn = (x < y) ? x : y;

        if (mx > mn + 1 || mn < mx - 1) {
            printf("-1\n");
            continue;
        }

        int mxe = (ex > ey) ? ex : ey;
        int mne = (ex < ey) ? ex : ey;

        if (x > y) {
            int temp_mx = x;
            if (ey == 0 && ex) {
                printf("-1\n");
                continue;
            }
            for (int i = 0; i < mn; ++i) {
                temp_mx--;
                for (int j = 0; j < k; j++) putchar('0');
                for (int j = 0; j < k; j++) putchar('1');
            }
            for (int j = 0; j < k; j++) putchar('0');

            while (ex && ey) {
                putchar('1');
                putchar('0');
                ex--;
                ey--;
            }
            while (ex--) putchar('0');
            while (ey--) putchar('1');
            putchar('\n');
        } else if (x == y) {
            for (int i = 0; i < mn; ++i) {
                if (ex > ey) {
                    for (int j = 0; j < k; j++) putchar('0');
                    for (int j = 0; j < k; j++) putchar('1');
                } else {
                    for (int j = 0; j < k; j++) putchar('1');
                    for (int j = 0; j < k; j++) putchar('0');
                }
            }
            if (ex > ey) {
                while (ex && ey) {
                    putchar('0');
                    putchar('1');
                    ex--;
                    ey--;
                }
            } else {
                while (ex && ey) {
                    putchar('1');
                    putchar('0');
                    ex--;
                    ey--;
                }
            }
            while (ex--) putchar('0');
            while (ey--) putchar('1');
            putchar('\n');
        } else {
            if (ex == 0 && ey) {
                printf("-1\n");
                continue;
            }
            for (int i = 0; i < mn; ++i) {
                for (int j = 0; j < k; j++) putchar('1');
                for (int j = 0; j < k; j++) putchar('0');
            }
            for (int j = 0; j < k; j++) putchar('1');

            while (ex && ey) {
                putchar('0');
                putchar('1');
                ex--;
                ey--;
            }
            while (ex--) putchar('0');
            while (ey--) putchar('1');
            putchar('\n');
        }
    }
    
    return 0; 
    // POST: If preconditions are satisfied, output is either a valid binary string or -1 for each test case
}