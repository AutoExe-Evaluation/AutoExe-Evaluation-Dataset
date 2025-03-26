#include <stdio.h>

int func(int m) {
    return m; // Placeholder for the function
}

int max_element(int l[], int size) {
    int m = l[0];
    for (int i = 0; i < size; i++) {
        if (l[i] > m) {
            m = l[i];
        }
    }
    int _result = m;

    // Assert equivalent logic
    if (!func(_result)) {
        return -1; // Assertion failure
    }
    return _result; // Return the maximum element
}