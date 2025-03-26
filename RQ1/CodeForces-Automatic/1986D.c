#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be between 1 and 10^4
    
    while (TCS--) 
    {
        int n;
        char s[21];
        scanf("%d %s", &n, s);
        
        assert(n >= 2 && n <= 20); // PRE: Length of string should be between 2 and 20
        assert(strlen(s) == n); // PRE: Length of the string should match n

        if (n == 2)
        {
            long result = strtol(s, NULL, 10);
            printf("%ld\n", result);
            assert(result >= 0 && result < 100); // POST: Result should be a valid digit value
            continue;
        }
        
        long long mn = LLONG_MAX;
        for (int i = 0; i < n - 1; i++)
        {
            int v[21], v_size = 0;
            long long sum = 0;

            for (int j = 0; j < i; j++)  
                v[v_size++] = s[j] - '0';

            v[v_size++] = strtol(s + i, NULL, 10);

            for (int j = i + 2; j < n; j++)  
                v[v_size++] = s[j] - '0';

            for (int j = 0; j < v_size; j++)
                for (int k = j + 1; k < v_size; k++)
                    if (v[j] > v[k])
                    {
                        int temp = v[j];
                        v[j] = v[k];
                        v[k] = temp;
                    }

            if (v[0] == 0) 
                mn = 0;

            for (int j = 0; j < v_size; j++)
            {
                if (v[j] != 1) 
                    sum += v[j];
            }
            
            if (sum == 0) 
                sum = 1;
                
            if (mn > sum) 
                mn = sum;
        }
        
        printf("%lld\n", mn);
        assert(mn >= 0); // POST: Minimum result should be non-negative
    }
    
    return 0;
}