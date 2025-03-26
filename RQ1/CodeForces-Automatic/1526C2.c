#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

struct MinHeap {
    ll* arr;
    int size;
    int capacity;
};

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->arr = (ll*)malloc(capacity * sizeof(ll));
    return minHeap;
}

void swap(ll* a, ll* b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void insert(struct MinHeap* minHeap, ll element) {
    if (minHeap->size < minHeap->capacity) {
        minHeap->arr[minHeap->size] = element;
        int i = minHeap->size;
        minHeap->size++;
        while (i != 0 && minHeap->arr[i] < minHeap->arr[(i - 1) / 2]) {
            swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

ll extractMin(struct MinHeap* minHeap) {
    if (minHeap->size == 0) return -1;
    ll root = minHeap->arr[0];
    if (minHeap->size > 1) {
        minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
        minHeap->size--;
        int i = 0;
        while (i < minHeap->size / 2) {
            int smallest = i;
            if (2 * i + 1 < minHeap->size && minHeap->arr[2 * i + 1] < minHeap->arr[smallest]) {
                smallest = 2 * i + 1;
            }
            if (2 * i + 2 < minHeap->size && minHeap->arr[2 * i + 2] < minHeap->arr[smallest]) {
                smallest = 2 * i + 2;
            }
            if (smallest == i) break;
            swap(&minHeap->arr[i], &minHeap->arr[smallest]);
            i = smallest;
        }
    }
    return root;
}

int main() {
    ll n, hp = 0;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 200000); // PRE: n is within the specified limits
    struct MinHeap* pq = createMinHeap(n);
    for (ll i = 0; i < n; ++i) {
        ll x;
        scanf("%lld", &x);
        assert(x >= -1000000000 && x <= 1000000000); // PRE: potion effect is within limits
        hp += x;
        insert(pq, x);
        while (hp < 0) {
            hp -= extractMin(pq);
        }
    }

    assert(pq->size >= 0 && pq->size <= n); // POST: the number of potions is valid
    printf("%d\n", pq->size);
    free(pq->arr);
    free(pq);
    return 0;
}