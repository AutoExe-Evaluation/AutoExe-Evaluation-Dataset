#include<stdio.h>
#include<assert.h>

#define int long long

void processArray(int n, int v[]) {
    assert(n >= 1); // PRE: Length of array must be at least 1
    if(v[0] == 1)
        v[0]++;
    for(int i = 1; i < n; ++i) {
        if(v[i] == 1)
            v[i]++;
        if(v[i] % v[i - 1] == 0)
            v[i]++;
    }
    for(int i = 0; i < n; i++)
        printf("%lld ", v[i]);
    printf("\n");
}

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be in [1, 10^4]
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 10000); // PRE: Length of each array must be in [1, 10^4]
        
        int v[n];
        for(int i = 0; i < n; i++)
            scanf("%lld", &v[i]);
        
        processArray(n, v);
        
        for(int i = 0; i < n; i++)
            assert(v[i] > 0); // POST: All elements in the array must remain positive
    }
    return 0;
}