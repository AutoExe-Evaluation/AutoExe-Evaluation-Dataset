#include <stdio.h>
#include <assert.h>

#define MAX_N 30

int home[MAX_N], away[MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 30); // PRE: Number of teams is between 2 and 30.
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &home[i], &away[i]);
        assert(home[i] != away[i]); // PRE: Home and away uniforms must be distinct.
    }

    int ct = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (home[i] == away[j]) {
                ct++;
            }
        }
    }

    printf("%d\n", ct);
    assert(ct >= 0); // POST: The count of games where the host plays in guest uniform is non-negative.
    
    return 0;
}