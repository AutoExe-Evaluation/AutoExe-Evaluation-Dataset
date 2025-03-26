#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long long accumulate(long long *arr, int size) {
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() 
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 <= t <= 100

    for (int TC = 1; TC <= TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 50); // PRE: 1 <= n <= 50

        long long *v = (long long *)malloc(n * sizeof(long long));
        for(int i = 0; i < n; i++) {
            scanf("%lld", &v[i]);
            assert(v[i] >= -1000 && v[i] <= 1000); // PRE: |a_i| <= 1000
        }
        
        if(n == 1) {
            printf("%lld\n", v[0]);
            free(v);
            continue;
        }
        
        long long mx = accumulate(v, n);
        long long *curr = v;
        
        for(int ops = 1; ops <= n; ops++) {
            int newSize = n - 1;
            long long *p = (long long *)malloc(newSize * sizeof(long long));
            for(int i = 0; i < newSize; i++) 
                p[i] = curr[i+1] - curr[i];

            long long *q = (long long *)malloc(n * sizeof(long long));
            for(int i = 0; i < n; i++)
                q[i] = curr[n - 1 - i];

            long long *dif = (long long *)malloc(newSize * sizeof(long long));
            for(int i = 0; i < newSize; i++)
                dif[i] = q[i+1] - q[i];
            
            mx = (mx > accumulate(p, newSize)) ? mx : accumulate(p, newSize);
            mx = (mx > accumulate(dif, newSize)) ? mx : accumulate(dif, newSize);
            
            if(newSize > 1) {
                free(curr);
                curr = p;
                n = newSize;
            } else {
                free(p);
                break;
            }
            
            free(q);
            free(dif);
        }
        
        printf("%lld\n", mx);
        assert(mx >= 0); // POST: result is non-negative
        free(curr);
    }
    return 0;
}