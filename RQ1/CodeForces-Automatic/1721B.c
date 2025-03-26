#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Ensure number of test cases is within limits

    while (TC--) {
        int n, m, s1, s2, d;
        scanf("%d %d %d %d %d", &n, &m, &s1, &s2, &d);
        assert(n >= 2 && n <= 1000 && m >= 2 && m <= 1000); // PRE: Ensure grid sizes are valid
        assert(s1 >= 1 && s1 <= n && s2 >= 1 && s2 <= m); // PRE: Ensure laser position is valid
        assert(d >= 0 && d <= n + m); // PRE: Ensure distance is valid
        
        int pass = 1;
        if (s1 + d >= n && s2 + d >= m) pass = 0;
        else if (s1 - d <= 1 && s2 - d <= 1) pass = 0;
        else if (s1 + d >= n && s1 - d <= 1) pass = 0;
        else if (s2 + d >= m && s2 - d <= 1) pass = 0;

        if (pass) {
            printf("%d\n", n + m - 2);
            assert(n + m - 2 >= 0); // POST: Ensure result is valid if path exists
        } else {
            printf("-1\n");
            assert(-1 == -1); // POST: Check the impossible case returns -1
        }
    }
    return 0;
}