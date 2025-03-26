#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4

    while (TCS--) {
        long long n, ans = 0;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 <= n <= 2 * 10^5
        long long* pq = (long long*)malloc(n * sizeof(long long));
        int pqSize = 0;

        for (int i = 0; i < n; ++i) {
            long long x;
            scanf("%lld", &x);
            assert(x >= 0 && x <= 1000000000); // PRE: 0 <= s_i <= 10^9
            if (x == 0 && pqSize > 0) {
                ans += pq[0];
                pq[0] = pq[pqSize - 1];
                pqSize--;
                // Simple max-heapify to maintain the heap property
                int j = 0, largest;
                while (2 * j + 1 < pqSize) {
                    largest = j;
                    if (pq[2 * j + 1] > pq[largest]) largest = 2 * j + 1;
                    if (2 * j + 2 < pqSize && pq[2 * j + 2] > pq[largest]) largest = 2 * j + 2;
                    if (largest == j) break;
                    long long temp = pq[j];
                    pq[j] = pq[largest];
                    pq[largest] = temp;
                    j = largest;
                }
            } else {
                pq[pqSize++] = x;
                // Simple insert to max-heap
                int i = pqSize - 1;
                while (i > 0) {
                    int parent = (i - 1) / 2;
                    if (pq[parent] >= pq[i]) break;
                    long long temp = pq[i];
                    pq[i] = pq[parent];
                    pq[parent] = temp;
                    i = parent;
                }
            }
        }
        
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Maximum possible total power is non-negative
        free(pq);
    }
    return 0;
}