#include <stdio.h>
#include <assert.h>

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases is within bounds

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 100000); // PRE: Length of the permutation is within bounds

        int v[n];
        int s = 1, e = n;

        for (int i = 1; i <= n; ++i) {
            if (i & 1)
                v[i - 1] = s++;
            else
                v[i - 1] = e--;
        }

        for (int i = 0; i < n; ++i)
            printf("%d ", v[i]);
        printf("\n");
        
        assert((n % 2 == 0 && v[0] == 1) || (n % 2 == 1 && v[0] == 1)); // POST: The first element should be 1
    }
    
    return 0;
}