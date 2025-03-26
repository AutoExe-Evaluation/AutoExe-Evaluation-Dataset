#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    
    assert(TC >= 1 && TC <= 100); // PRE: number of test cases should be between 1 and 100

    while (TC--) {
        int n;
        scanf("%lld", &n);
        
        assert(n >= 1 && n <= 1000); // PRE: n should be between 1 and 1000

        if (n % 3) {
            printf("First\n");
            assert(n % 3 != 0); // POST: Vanya wins if n % 3 is not 0
        } else {
            printf("Second\n");
            assert(n % 3 == 0); // POST: Vova wins if n % 3 is 0
        }
    }
    return 0;
}