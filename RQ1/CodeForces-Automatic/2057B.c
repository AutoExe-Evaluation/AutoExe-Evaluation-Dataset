#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <assert.h>

#define int long long

bool pred(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // PRE: t cases are to be processed with valid n and k values
    int TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 ≤ t ≤ 10^4

    while (TCS--) {
        int n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= 1 && n <= 100000); // PRE: 1 ≤ n ≤ 10^5
        assert(k >= 0 && k <= n); // PRE: 0 ≤ k ≤ n

        std::map<int, int> m;

        for(int i = 0; i < n; ++i) {
            int x;
            scanf("%lld", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            m[x]++;
        }

        int *v = (int*)malloc(m.size() * sizeof(int));
        int index = 0;
        for(auto it = m.begin(); it != m.end(); ++it) {
            v[index++] = it->second;
        }

        // Sorting the occurrences
        qsort(v, index, sizeof(int), pred);

        for(int i = 0; i < index; ++i) {
            if(v[i] > k) {
                printf("%lld\n", index - i);
                free(v);
                // POST: f(a) is minimized after changes
                assert(f(a) == index - i); // POST: minimal operations achieved
                return 0;
            }
            k -= v[i];
        }
        printf("1\n");
        free(v);
        // POST: f(a) is minimized after changes
        assert(f(a) == 1); // POST: minimal operations achieved
    }
    return 0;
}
