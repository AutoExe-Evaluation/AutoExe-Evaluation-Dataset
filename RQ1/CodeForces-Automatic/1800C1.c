#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

struct Node {
    ll value;
    struct Node* next;
};

struct MaxHeap {
    struct Node* head;
};

void push(struct MaxHeap* heap, ll value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = heap->head;
    heap->head = newNode;
}

ll top(struct MaxHeap* heap) {
    if (heap->head != NULL) {
        return heap->head->value;
    }
    return 0;
}

void pop(struct MaxHeap* heap) {
    if (heap->head != NULL) {
        struct Node* temp = heap->head;
        heap->head = heap->head->next;
        free(temp);
    }
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: Number of test cases is within range

    while (TCS--) {
        ll n, ans = 0;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 5000); // PRE: Number of cards is within range
        struct MaxHeap pq;
        pq.head = NULL;

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            assert(x >= 0 && x <= 1000000000); // PRE: Card power is within range
            if (x == 0 && pq.head != NULL) {
                ans += top(&pq);
                pop(&pq);
            } else {
                push(&pq, x);
            }
        }
        printf("%lld\n", ans);
        assert(ans >= 0); // POST: Total power of army is non-negative
    }
    return 0;
}