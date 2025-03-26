#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

int main() {
    ll n, hp = 0;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 2000); // PRE: 1 <= n <= 2000
    ll *pq = (ll *)malloc(n * sizeof(ll));
    int pq_size = 0;

    for (ll i = 0; i < n; ++i) {
        ll x;
        scanf("%lld", &x);
        hp += x;
        pq[pq_size++] = x;
        
        // Min-heap adjustment
        for (int j = pq_size / 2 - 1; j >= 0; --j) {
            int smallest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;
            if (left < pq_size && pq[left] < pq[smallest]) {
                smallest = left;
            }
            if (right < pq_size && pq[right] < pq[smallest]) {
                smallest = right;
            }
            if (smallest != j) {
                ll temp = pq[j];
                pq[j] = pq[smallest];
                pq[smallest] = temp;
            }
        }

        while (hp < 0) {
            hp -= pq[0];
            pq[0] = pq[--pq_size];
            for (int j = pq_size / 2 - 1; j >= 0; --j) {
                int smallest = j;
                int left = 2 * j + 1;
                int right = 2 * j + 2;
                if (left < pq_size && pq[left] < pq[smallest]) {
                    smallest = left;
                }
                if (right < pq_size && pq[right] < pq[smallest]) {
                    smallest = right;
                }
                if (smallest != j) {
                    ll temp = pq[j];
                    pq[j] = pq[smallest];
                    pq[smallest] = temp;
                }
            }
        }
    }

    printf("%d\n", pq_size);
    assert(hp >= 0); // POST: health should be non-negative at the end
    free(pq);
    return 0;
}