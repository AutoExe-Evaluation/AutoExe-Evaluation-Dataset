#include <stdio.h>
#include <assert.h>

int main() {
    int TCS = 0;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4

    for (int TC = 1; TC <= TCS; ++TC) {
        long long n, a, b;
        scanf("%lld %lld %lld", &n, &a, &b);
        assert(n >= 1 && n <= 10000000); // PRE: 1 ≤ n ≤ 10^7
        assert(a >= 1 && a <= 50); // PRE: 1 ≤ a ≤ 50
        assert(b >= 1 && b <= 50); // PRE: 1 ≤ b ≤ 50

        long long quests;
        if (a > b) {
            quests = 1;
        } else {
            quests = (n + a - 1) / a;
        }
        
        printf("%lld\n", quests);
        assert(quests >= 1); // POST: quests should be at least 1
    }

    return 0;
}