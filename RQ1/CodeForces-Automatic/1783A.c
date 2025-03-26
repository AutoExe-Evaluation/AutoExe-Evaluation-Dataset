#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 2000); // PRE: 1 <= t <= 2000

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 50); // PRE: 2 <= n <= 50

        int *v = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 100); // PRE: 1 <= a_i <= 100
        }

        // Sort the array
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < n - i - 1; j++) {
                if(v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        
        if(v[0] == v[n - 1]) {
            printf("NO\n");
            assert(!(v[0] < v[n - 1]); // POST: Not possible to create a beautiful array
        } else {
            printf("YES\n");
            printf("%lld ", v[n - 1]);
            for(int i = 0; i < n - 1; i++)
                printf("%lld ", v[i]);
            printf("\n");
            assert(v[n - 1] != 0); // POST: The array must be beautiful
        }

        free(v);
    }
    return 0;
}