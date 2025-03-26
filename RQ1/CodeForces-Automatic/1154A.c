#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int v[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &v[i]);
        assert(v[i] > 0); // PRE: Each number must be positive
    }
    
    qsort(v, 4, sizeof(int), cmp);

    int a = v[3] - v[0];
    int b = v[3] - v[1];
    int c = v[3] - v[2];
    
    assert(a > 0 && b > 0 && c > 0); // POST: a, b, and c must be positive integers
    printf("%d %d %d\n", a, b, c);
    
    return 0;
}