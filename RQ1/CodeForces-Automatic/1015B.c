#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int n;
    char s[51], t[51];
    scanf("%d %s %s", &n, s, t);
    
    assert(n >= 1 && n <= 50); // PRE: length of strings is within bounds
    assert(strlen(s) == n && strlen(t) == n); // PRE: both strings have the same length

    int v[10000], k = 0;

    for(int i = 0; i < n; ++i) {
        if(s[i] == t[i]) continue;
        int p = -1;
        for(int j = i + 1; j < n; ++j) {
            if(s[j] == t[i]) {
                p = j;
                break;
            }
        }
        if(p == -1) {
            printf("-1\n");
            return 0;
        }
        for(int j = p - 1; j >= i; --j) {
            char temp = s[j];
            s[j] = s[j + 1];
            s[j + 1] = temp;
            v[k++] = j;
        }
    }
    
    printf("%d\n", k);
    for(int i = 0; i < k; ++i) {
        printf("%d ", v[i] + 1);
    }
    printf("\n");
    
    assert(strcmp(s, t) == 0); // POST: resultant s should equal t
    assert(k <= 10000); // POST: number of moves should not exceed 10^4
    return 0;
}