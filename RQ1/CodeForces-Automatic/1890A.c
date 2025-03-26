#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

int main() {
    int TC;
    scanf("%d", &TC); // PRE: TC > 0, a number of test cases
    
    // Process each test case
    while (TC--) {
        int n;
        scanf("%d", &n); // PRE: n >= 2, length of the array
        int a[MAX_SIZE] = {0};
        int count[100001] = {0};

        // Read the array and count occurrences
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            count[a[i]]++;
        }

        int unique_count = 0;
        for (int i = 1; i <= 100000; i++) {
            if (count[i] > 0) {
                unique_count++;
            }
        }

        // Assert: unique_count indicates the correct number of unique elements
        assert(unique_count <= 100); // POST: at most 100 unique elements

        if (unique_count > 2) {
            printf("NO\n"); // POST: not possible to create a good array
        } else if (unique_count == 1) {
            printf("YES\n"); // POST: all elements are the same, hence good
        } else {
            bool valid = true;
            for (int i = 1; i <= 100000; i++) {
                if (count[i] > 0 && count[i] < n / 2) {
                    valid = false; // not enough occurrences of this element
                    break;
                }
            }
            if (valid) {
                printf("YES\n"); // POST: a good array can be formed
            } else {
                printf("NO\n"); // POST: cannot form a good array
            }
        }
    }
    return 0;
}