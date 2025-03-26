#include <stdio.h>
#include <assert.h>

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: number of test cases within valid range
    while (TC--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a >= 1 && a <= 100); // PRE: a within valid range
        assert(b >= 1 && b <= 100); // PRE: b within valid range
        assert(c >= 1 && c <= 100); // PRE: c within valid range

        int mn = a < b ? a : b;
        int mx = a > b ? a : b;
        int ct = 0;
        while (mn < mx) {
            mn += c;
            mx -= c;
            ct++;
        }
        printf("%d\n", ct);
        assert(mn == mx); // POST: masses of water in the vessels are equal
    }
    return 0;
}