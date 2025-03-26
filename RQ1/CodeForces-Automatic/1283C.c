#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 200000

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 200000); // PRE: n is between 2 and 200000
    long long f[MAX_N + 1];
    long long mp[MAX_N + 1] = {0};
    
    for (long long i = 1; i <= n; i++) {
        scanf("%lld", &f[i]);
        assert(f[i] == 0 || (f[i] >= 1 && f[i] <= n && f[i] != i)); // PRE: f_i is valid
        if (f[i]) mp[f[i]]++;
    }

    long long cycle[MAX_N], in[MAX_N], out[MAX_N];
    long long cycle_size = 0, in_size = 0, out_size = 0;
    
    for (long long i = 1; i <= n; ++i) {
        if (f[i] == 0 && mp[i] == 0) cycle[cycle_size++] = i;
        else if (f[i] == 0) out[out_size++] = i;
        else if (mp[i] == 0) in[in_size++] = i;
    }

    if (cycle_size == 1) {
        f[out[0]] = cycle[0];
        f[cycle[0]] = in[0];
        out_size--;
        in_size--;  
    } else if (cycle_size > 1) {
        for (long long i = 0; i < cycle_size - 1; i++)
            f[cycle[i]] = cycle[i + 1];
        f[cycle[cycle_size - 1]] = cycle[0];
    }

    for (long long i = 0; i < in_size; ++i)
        f[out[i]] = in[i];
    
    for (long long i = 1; i <= n; ++i) 
        assert(f[i] != i); // POST: no friend gives a gift to himself 
    printf("\n"); // Ensuring output format compatibility with requirements
    for (long long i = 1; i <= n; ++i)  
        printf("%lld ", f[i]);
    printf("\n");
    
    return 0;
}