#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct Deque {
    struct Node* front;
    struct Node* back;
    int size;
};

void initDeque(struct Deque* d) {
    d->front = NULL;
    d->back = NULL;
    d->size = 0;
}

void pushFront(struct Deque* d, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = d->front;
    newNode->prev = NULL;
    if (d->front != NULL) {
        d->front->prev = newNode;
    }
    d->front = newNode;
    if (d->back == NULL) {
        d->back = newNode;
    }
    d->size++;
}

void popBack(struct Deque* d) {
    if (d->back != NULL) {
        struct Node* toDelete = d->back;
        d->back = d->back->prev;
        if (d->back != NULL) {
            d->back->next = NULL;
        } else {
            d->front = NULL;
        }
        free(toDelete);
        d->size--;
    }
}

int contains(struct Node* front, int value) {
    struct Node* current = front;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void freeDeque(struct Deque* d) {
    struct Node* current = d->front;
    while (current != NULL) {
        struct Node* toDelete = current;
        current = current->next;
        free(toDelete);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    assert(n > 0 && k > 0); // PRE: n and k must be positive numbers.

    int* seen = (int*)calloc(1000000001, sizeof(int));
    struct Deque d;
    initDeque(&d);
    
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (seen[x]) continue;
        if (d.size >= k) {
            int y = d.back->value;
            popBack(&d);
            seen[y] = 0;
        }
        pushFront(&d, x);
        seen[x] = 1;
    }
    
    printf("%d\n", d.size);
    struct Node* current = d.front;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
    
    assert(d.size <= k); // POST: number of conversations displayed is less than or equal to k.
    
    free(seen);
    freeDeque(&d);
    
    return 0;
}