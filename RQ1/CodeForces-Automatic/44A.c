#include <stdio.h>
#include <string.h>
#include <assert.h>

struct Leaf {
    char species[11];
    char color[11];
};

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: Number of leaves must be between 1 and 100

    struct Leaf leaves[100];
    int unique_count = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%s %s", leaves[i].species, leaves[i].color);
        int is_unique = 1;

        for (int j = 0; j < unique_count; ++j) {
            if (strcmp(leaves[i].species, leaves[j].species) == 0 && 
                strcmp(leaves[i].color, leaves[j].color) == 0) {
                is_unique = 0;
                break;
            }
        }
        
        if (is_unique) {
            leaves[unique_count++] = leaves[i];
        }
    }

    printf("%d\n", unique_count);
    assert(unique_count >= 0 && unique_count <= n); // POST: Unique count must be between 0 and n
    return 0;
}