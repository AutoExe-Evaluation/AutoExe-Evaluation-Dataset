void sort_even(int l[], int size) {
    int evens[size / 2 + 1]; // considering the case if size is odd
    int odds[size / 2 + 1];
    int even_count = 0, odd_count = 0;
    
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            evens[even_count++] = l[i];
        } else {
            odds[odd_count++] = l[i];
        }
    }

    // Sort evens using a simple sorting algorithm (e.g., bubble sort)
    for (int i = 0; i < even_count - 1; i++) {
        for (int j = 0; j < even_count - i - 1; j++) {
            if (evens[j] > evens[j + 1]) {
                int temp = evens[j];
                evens[j] = evens[j + 1];
                evens[j + 1] = temp;
            }
        }
    }

    int ans[size];
    int index = 0;

    for (int i = 0; i < odd_count; i++) {
        ans[index++] = evens[i];
        ans[index++] = odds[i];
    }

    if (even_count > odd_count) {
        ans[index++] = evens[even_count - 1];
    }

    // Assuming func is defined elsewhere
    assert(func(ans));
}