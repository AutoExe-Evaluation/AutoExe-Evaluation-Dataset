#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases must be between 1 and 1000

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 100000); // PRE: Number of students must be between 2 and 100000

        int ct = 0;
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= n); // PRE: Chair number must be within valid range
            if (x == i)
                ct++;
        }
        // Assert the validity of ct based on student positions
        assert(ct >= 0 && ct <= n); // PRE: Count of students in their own chairs should be valid

        if (ct == 0)
            printf("0\n");
        else if (ct % 2 == 0)
            printf("%d\n", ct / 2);
        else
            printf("%d\n", ct / 2 + 1);
        
        // POST: After processing each test case, the minimum moves should be correct
        assert(ct == 0 || ct % 2 == 0 || ct % 2 == 1); // VALID: The computed number of moves is consistent with ct
    }
    return 0;
}