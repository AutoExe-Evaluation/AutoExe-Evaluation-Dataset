#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_CONVERSATIONS 200

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    assert(n >= 1 && n <= 200); // PRE: n should be within specified constraints
    assert(k >= 1 && k <= 200); // PRE: k should be within specified constraints
    
    bool mp[1000000000] = {false}; // To track if a conversation is currently displayed
    int d[MAX_CONVERSATIONS];
    int size = 0;

    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        
        if (mp[x]) continue;
        if (size >= k) {
            int y = d[size - 1];
            mp[y] = false;
            size--;
        }
        for (int j = size; j > 0; --j) {
            d[j] = d[j - 1]; // Shift conversations down
        }
        d[0] = x; // Add new conversation to the top
        mp[x] = true;
        size++;
    }
    
    printf("%d\n", size);
    for (int i = 0; i < size; ++i) {
        printf("%d ", d[i]);
    }
    printf("\n");
    
    assert(size >= 1 && size <= (n < k ? n : k)); // POST: size should be within valid limits
    
    return 0;
}