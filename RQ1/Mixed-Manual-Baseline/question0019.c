#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode *a, *b, *p = NULL, *orig = head;
    a = b = head;
    while (n-- > 0) {       // b moves n steps first
        b = b->next;
    }
    
    while (b) {             // a, b move together, keeps a gap of n steps
        p = a;
        a = a->next;
        b = b->next;
    }
    
    if (a == head) {        // a is the one to be removed
        head = a->next;
    } else {
        p->next = a->next;
    }
    free(a);
    
    assert(head == orig); // POST
    return head;
}

int main()
{
    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->data = 1;
    head->next = malloc(sizeof(struct ListNode));
    head->next->data = 2;
    head->next->next = malloc(sizeof(struct ListNode));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    int n;
    klee_make_symbolic(&n, sizeof(n), "n");
    klee_assume(n >= 0 && n <= 3);
}
