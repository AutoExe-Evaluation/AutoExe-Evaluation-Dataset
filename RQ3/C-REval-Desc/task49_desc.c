int digits_sum(int n) {
    int neg = 1;
    if (n < 0) {
        n = -n;
        neg = -1;
    }
    int sum = 0;
    while (n != 0) {
        sum += (n % 10) * neg;
        n /= 10;
    }
    return sum;
}

int count_nums(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (digits_sum(arr[i]) > 0) {
            count++;
        }
    }
    return count;
}

// Assertion function should be implemented elsewhere, e.g. assert(func(count_nums(arr, size)));