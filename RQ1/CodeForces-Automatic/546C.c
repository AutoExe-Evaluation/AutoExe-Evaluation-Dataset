#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    long long* arr;
    int front, rear, size, capacity;
} deque;

deque* createDeque(int capacity) {
    deque* d = (deque*)malloc(sizeof(deque));
    d->capacity = capacity;
    d->front = -1;
    d->rear = 0;
    d->size = 0;
    d->arr = (long long*)malloc(sizeof(long long) * capacity);
    return d;
}

int isEmpty(deque* d) {
    return d->size == 0;
}

void pushBack(deque* d, long long x) {
    d->arr[d->rear] = x;
    d->rear = (d->rear + 1) % d->capacity;
    d->size++;
}

long long popFront(deque* d) {
    if (isEmpty(d)) return -1;
    d->front = (d->front + 1) % d->capacity;
    d->size--;
    return d->arr[d->front];
}

void freeDeque(deque* d) {
    free(d->arr);
    free(d);
}

int main() {
    long long n, mx = 1;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 10); // PRE: n is between 2 and 10
    for (long long i = 2; i <= n; ++i)
        mx *= i;

    deque* a = createDeque(n);
    deque* b = createDeque(n);

    long long k1;
    scanf("%lld", &k1);
    assert(k1 >= 1 && k1 <= n - 1); // PRE: k1 is between 1 and n-1
    for (long long i = 0; i < k1; ++i) {
        long long x;
        scanf("%lld", &x);
        pushBack(a, x);
    }

    long long k2 = n - k1;
    assert(k2 >= 1 && k2 <= n - 1); // PRE: k2 is between 1 and n-1
    for (long long i = 0; i < k2; ++i) {
        long long x;
        scanf("%lld", &x);
        pushBack(b, x);
    }

    long long ct = 0;
    while (!isEmpty(a) && !isEmpty(b)) {
        long long x = popFront(a);
        long long y = popFront(b);
        if (x > y) {
            pushBack(a, y);
            pushBack(a, x);
        } else {
            pushBack(b, x);
            pushBack(b, y);
        }
        ct++;

        if (ct > mx) {
            printf("-1\n");
            freeDeque(a);
            freeDeque(b);
            return 0;
        }
    }
    printf("%lld %lld\n", ct, isEmpty(a) ? 2 : 1);
    freeDeque(a);
    freeDeque(b);
    assert(ct <= mx); // POST: ct should not exceed max fights
    return 0;
}
