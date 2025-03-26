#include <stdio.h>
#include <assert.h>

int main() {
    long long TCS = 1;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 100000); // PRE: number of test cases should be within range

    for (long long TC = 1; TC <= TCS; ++TC) {
        long long b, c, d;  
        scanf("%lld %lld %lld", &b, &c, &d);
        assert(b >= 0 && b <= 1000000000000000000); // PRE: b should be non-negative and within range
        assert(c >= 0 && c <= 1000000000000000000); // PRE: c should be non-negative and within range
        assert(d >= 0 && d <= 1000000000000000000); // PRE: d should be non-negative and within range
        
        long long a = 0;  

        for (int i = 0; i < 61; ++i) {
            int bi = (b >> i) & 1;  
            int ci = (c >> i) & 1;  
            int di = (d >> i) & 1;
            if (di == 1) {
                if (bi == 0 && ci == 1) {
                    printf("-1\n");
                    break; // Exit the loop and proceed to the next case
                }
                if (bi == 0 && ci == 0) a |= (1ll << i);
                else if (bi == 1 && ci == 0) a |= (1ll << i);
            } else {
                if (bi == 1 && ci == 0) {
                    printf("-1\n");
                    break; // Exit the loop and proceed to the next case
                }
                if (bi == 1 && ci == 1) a |= (1ll << i);
                else if (bi == 0 && ci == 1) a |= (1ll << i);
            }  
        }
        
        if (a > (1ll << 61)) {
            printf("-1\n");
        } else {
            printf("%lld\n", a);
            assert(((a | b) - (a & c)) == d); // POST: The condition should satisfy the equation
        }
    }
    return 0;
}