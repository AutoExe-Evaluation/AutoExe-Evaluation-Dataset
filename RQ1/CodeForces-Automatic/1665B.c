#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    Pair* array;
    int size;
    int capacity;
} Map;

void initMap(Map* m, int capacity) {
    m->array = (Pair*)malloc(capacity * sizeof(Pair));
    m->size = 0;
    m->capacity = capacity;
}

void insert(Map* m, int key) {
    for (int i = 0; i < m->size; i++) {
        if (m->array[i].key == key) {
            m->array[i].value++;
            return;
        }
    }
    if (m->size < m->capacity) {
        m->array[m->size].key = key;
        m->array[m->size].value = 1;
        m->size++;
    }
}

void freeMap(Map* m) {
    free(m->array);
}

int solve(int n) {
    Map m;
    initMap(&m, n);
    
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        insert(&m, x);
    }

    assert(m.size > 0); // PRE: At least one element in the map
    if (m.size == 1) {
        freeMap(&m);
        return 0;
    }

    int ct = 0;
    for (int i = 0; i < m.size; i++) {
        if (m.array[i].value > ct) {
            ct = m.array[i].value;
        }
    }
    int r = n - ct;
    int ans = 0;
    while (ct < n) {
        ans += (r < ct ? r : ct) + 1;
        r -= ct;
        ct *= 2;
    }

    freeMap(&m);
    assert(ans >= 0); // POST: Answer must be non-negative
    return ans;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Constraints for TCS
    for (int TC = 1; TC <= TCS; TC++) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100000); // PRE: Constraints for n
        int result = solve(n);
        printf("%d\n", result);
    }
    return 0;
}