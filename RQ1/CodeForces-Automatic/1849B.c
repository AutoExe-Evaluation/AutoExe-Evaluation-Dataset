#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int ll;

typedef struct {
    ll first;
    ll second;
} pair;

int cmp(const void *a, const void *b) {
    pair *pa = (pair *)a;
    pair *pb = (pair *)b;
    if(pa->first == pb->first)
        return pa->second - pb->second;
    return pb->first - pa->first;
}

int main() {
    ll TC;
    scanf("%lld", &TC);
    
    // PRE: TC >= 1
    assert(TC >= 1);
    
    while (TC--) {
        ll n, k;
        scanf("%lld %lld", &n, &k);
        
        // PRE: n >= 1, k >= 1
        assert(n >= 1 && k >= 1);
        
        pair *v = (pair *)malloc(n * sizeof(pair));
        for(ll i = 0; i < n; ++i) {
            ll x;
            scanf("%lld", &x);
            if(x % k)
                x %= k;
            else
                x = k;
            v[i].first = x;
            v[i].second = i + 1;
        }
        
        qsort(v, n, sizeof(pair), cmp);
        for(ll i = 0; i < n; ++i)
            printf("%lld ", v[i].second);
        printf("\n");
        free(v);
    }
    
    // POST: Indices of monsters in the order they die are printed
    assert(TC >= 1);
    return 0;
}