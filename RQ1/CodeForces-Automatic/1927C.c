#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 200005

int a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int TC;
    scanf("%d", &TC);
    
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases should be between 1 and 10^4

    while (TC--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        
        assert(n >= 1 && n <= 200000); // PRE: n should be between 1 and 2*10^5
        assert(m >= 1 && m <= 200000); // PRE: m should be between 1 and 2*10^5
        assert(k >= 2 && k <= 2 * (n < m ? n : m) && k % 2 == 0); // PRE: k is even and within constraints

        int countA[1000006] = {0}; 
        int countB[1000006] = {0}; 
        int uniqueCount = 0;
        
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] <= k && countA[a[i]] == 0) {
                countA[a[i]] = 1;
                uniqueCount++;
            }
        }
        for(int i = 0; i < m; ++i) {
            scanf("%d", &b[i]);
            if (b[i] <= k && countB[b[i]] == 0) {
                countB[b[i]] = 1;
                uniqueCount++;
            }
        }

        int ct1 = 0, ct2 = 0;
        for(int i = 1; i <= k; i++) {
            if (countA[i]) ct1++;
            if (countB[i]) ct2++;
        }

        // POST: uniqueCount should match k and ct1 and ct2 should be at least k/2
        assert(uniqueCount == k && ct1 >= k / 2 && ct2 >= k / 2); 

        if (uniqueCount == k && ct1 >= k / 2 && ct2 >= k / 2)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}