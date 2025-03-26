#include <stdio.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 5000); // PRE: Number of test cases should be in range [1, 5000]
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 50); // PRE: Number of friends should be in range [2, 50]
        int v[50];
        
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: Each friend's best friend index should be in valid range
        }
        
        int minInvitations = 3; // Default assumption
        for (int i = 0; i < n; ++i) {
            int fnd = i + 1;
            int bst = v[i];
            if (v[bst - 1] == fnd) {
                minInvitations = 2;
                break; // Found a pair, no need to check further
            }
        }
        
        printf("%d\n", minInvitations);
        assert(minInvitations >= 2); // POST: At least 2 friends should be invited
    }
    
    return 0;
}