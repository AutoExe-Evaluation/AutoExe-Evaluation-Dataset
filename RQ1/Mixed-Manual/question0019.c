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
}
