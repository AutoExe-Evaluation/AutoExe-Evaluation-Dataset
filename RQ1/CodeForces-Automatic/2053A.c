#include <stdio.h>
#include <assert.h>

#define int long long
#define MAX_N 200

int main() {
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 200); // PRE: Number of test cases is within bounds
    
    while (TCS--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 200); // PRE: Length of array is within bounds
        int v[MAX_N];
        
        for (int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= 1 && v[i] <= 100000); // PRE: Each element in the array is within bounds
        }
        
        int found = 0;
        for (int i = 1; i < n; i++) {
            int p = 2 * (v[i] < v[i - 1] ? v[i] : v[i - 1]);
            int q = (v[i] > v[i - 1] ? v[i] : v[i - 1]);
            if (p > q) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        
        assert(found == 1 || found == 0); // POST: Found should indicate if a valid partition exists
    }
    
    return 0;
}