#include <stdio.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC); // PRE: 1 <= TC <= 100
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases should be within the specified limits.

    while (TC--) {
        int n;
        scanf("%d", &n); // PRE: 3 <= n <= 100
        assert(n >= 3 && n <= 100); // PRE: Length of the array should be within the specified limits.
        
        int a[100];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]); // PRE: 1 <= a[i] <= 100
            assert(a[i] >= 1 && a[i] <= 100); // PRE: Each array element should be within the specified limits.
        }
        
        int unique_index = -1;
        for (int i = 1; i < n - 1; ++i) {
            if (a[i] != a[i - 1] && a[i] != a[i + 1]) {
                unique_index = i + 1; // Store the 1-based index
                break;
            }
        }
        
        if (unique_index == -1) {
            if (a[0] != a[n / 2]) 
                unique_index = 1; // The unique element is the first one
            else 
                unique_index = n; // The unique element is the last one
        }
        
        printf("%d\n", unique_index); // POST: The output index is the position of the unique element.
        assert(unique_index >= 1 && unique_index <= n); // POST: The index of the unique element must be a valid position in the array.
    }
    
    return 0;
}