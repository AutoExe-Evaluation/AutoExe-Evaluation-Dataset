int* get_odd_collatz(int n, int* returnSize) {
    int* odd_collatz;
    int capacity = 10;
    odd_collatz = (int*)malloc(capacity * sizeof(int));
    
    if (n % 2 != 0) {
        odd_collatz[0] = n;
        *returnSize = 1;
    } else {
        *returnSize = 0;
    }
    
    while (n > 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = n * 3 + 1;
            if (*returnSize >= capacity) {
                capacity *= 2;
                odd_collatz = (int*)realloc(odd_collatz, capacity * sizeof(int));
            }
            odd_collatz[(*returnSize)++] = n;
        }
    }
    
    // Sort odd_collatz
    for (int i = 0; i < *returnSize - 1; i++) {
        for (int j = 0; j < *returnSize - i - 1; j++) {
            if (odd_collatz[j] > odd_collatz[j + 1]) {
                int temp = odd_collatz[j];
                odd_collatz[j] = odd_collatz[j + 1];
                odd_collatz[j + 1] = temp;
            }
        }
    }

    assert(func(odd_collatz, *returnSize));
    return odd_collatz;
}