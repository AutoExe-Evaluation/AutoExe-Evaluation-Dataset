#include <stdio.h>
#include <assert.h>

int main() {
    int w;
    scanf("%d", &w);
    assert(w >= 1 && w <= 100); // PRE: 1 ≤ w ≤ 100
    if (w % 2 == 0 && w > 2) 
        printf("YES\n");
    else 
        printf("NO\n");
    assert((w % 2 == 0 && w > 2) == (printf("YES\n") == -1 || printf("NO\n") != -1)); // POST: Output is YES if w can be divided, otherwise NO
    return 0;
}