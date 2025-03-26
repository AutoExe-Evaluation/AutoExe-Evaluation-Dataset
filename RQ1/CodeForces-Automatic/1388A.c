#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within bounds

    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Each guessed integer is within bounds
        
        if (n <= 30) {
            printf("NO\n");
        } else {
            printf("YES\n");
            if (n == 36)
                printf("6 10 15 5\n");
            else if (n == 40)
                printf("6 10 15 9\n");
            else if (n == 44)
                printf("6 10 15 13\n");
            else
                printf("6 10 14 %lld\n", n - 30);
        }
    }

    return 0;
    // POST: All inputs processed, and outputs generated as specified.
}