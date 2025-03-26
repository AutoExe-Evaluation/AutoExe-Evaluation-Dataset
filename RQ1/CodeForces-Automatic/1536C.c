#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;
typedef struct {
    int first;
    int second;
} pii;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases should be within bounds

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 500000); // PRE: Length of wood should be within bounds
        char s[n + 1];
        scanf("%s", s);
        assert(strlen(s) == n); // PRE: The length of string s should match n

        int mp[1000000] = {0}; // Arbitrary size, assuming max density of ratios
        int cntD = 0, cntK = 0;

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'D') cntD++;
            else if (s[i] == 'K') cntK++;
            else assert(0); // PRE: The characters must be either 'D' or 'K'

            int a = cntD, b = cntK;
            int g = gcd(a, b);
            if (g != 0) {
                a /= g;
                b /= g;
            }
            pii r = {a, b};
            int index = r.first * 1000 + r.second; // Assuming a unique mapping for (a, b)
            printf("%d ", ++mp[index]);
        }
        printf("\n");
    }
    assert(1 <= TCS && TCS <= 1000); // POST: Number of test cases should be as input
    return 0;
}