#include <stdio.h>
#include <assert.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    assert(n >= 3 && n <= 50 && n % 2 == 1); // PRE: n is odd and within bounds
    assert(m >= 3 && m <= 50); // PRE: m is within bounds
    int right = 1, left = 1;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++)
                putchar('#');
            putchar('\n');
        } else if (right) {
            for (int j = 0; j < m - 1; j++)
                putchar('.');
            putchar('#');
            putchar('\n');
            right = 0;
            left = 1;
        } else if (left) {
            putchar('#');
            for (int j = 0; j < m - 1; j++)
                putchar('.');
            putchar('\n');
            right = 1;
            left = 0;
        }
    }
    
    // POST: The output consists of n lines with m characters as specified
    assert(n % 2 == 1); // Ensure n is still odd
    assert(n >= 3 && n <= 50); // Ensure n is within bounds
    assert(m >= 3 && m <= 50); // Ensure m is within bounds
    
    return 0;
}