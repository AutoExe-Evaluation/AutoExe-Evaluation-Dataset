#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    Pair *pairs;
    int size;
    int capacity;
} Map;

void initMap(Map *m, int capacity) {
    m->pairs = (Pair *)malloc(sizeof(Pair) * capacity);
    m->size = 0;
    m->capacity = capacity;
}

void insertMap(Map *m, int key) {
    for (int i = 0; i < m->size; ++i) {
        if (m->pairs[i].key == key) {
            m->pairs[i].value++;
            return;
        }
    }
    if (m->size == m->capacity) {
        m->capacity *= 2;
        m->pairs = (Pair *)realloc(m->pairs, sizeof(Pair) * m->capacity);
    }
    m->pairs[m->size].key = key;
    m->pairs[m->size].value = 1;
    m->size++;
}

int main() {
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: 1 <= t <= 10^4
    
    while (TCS--) {
        long long n, k;
        scanf("%lld %lld", &n, &k);
        assert(n >= k && n <= 200000); // PRE: 1 <= k <= n <= 200,000

        Map m;
        initMap(&m, n);
        
        for (long long i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            insertMap(&m, x);
        }
        
        long long mx = 0, ct = 0, last = -1, i = -1;
        for (int j = 0; j < m.size; ++j) {
            int x = m.pairs[j].key;
            int y = m.pairs[j].value;

            if (x != last + 1) {
                i = x;
                ct = 0;
            }
            if (x - i >= k) {
                ct -= m.pairs[j - k].value;
            }
            ct += y;
            last = x;
            if (ct > mx) {
                mx = ct;
            }
        }
        
        printf("%lld\n", mx);
        free(m.pairs);
    }

    assert(n > 0); // POST: Ensure at least one card is processed
    return 0;
}