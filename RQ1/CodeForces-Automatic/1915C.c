#include<stdio.h>
#include<math.h>
#include<assert.h>

#define int long long

int is_square(int num) {
    int x = sqrt(num);
    return x * x == num;
}

int main() {
    int TC = 0;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases is within bounds
    while (TC--) {
        int n = 0;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Number of buckets is within bounds
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: Number of squares in each bucket is within bounds
            sum += x;
        }
        // Check the postcondition
        assert(is_square(sum) || sum >= 0); // POST: Sum must be non-negative, can be square or not
        if (is_square(sum))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}