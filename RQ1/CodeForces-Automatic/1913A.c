#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    
    while (TC--) {
        char s[9];
        scanf("%s", s);
        assert(strlen(s) >= 2 && strlen(s) <= 8); // PRE: length of s should be between 2 and 8
        
        int len = strlen(s);
        int found = 0;

        for (int i = 1; i < len; ++i) {
            char a[9], b[9];
            strncpy(a, s, i);
            a[i] = '\0';
            strcpy(b, s + i);
            
            long long x = atoll(a);
            long long y = atoll(b);
            
            if (x < y && a[0] != '0' && b[0] != '0') {
                printf("%lld %lld\n", x, y);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("-1\n");
        }
        
        assert(found == 1 || found == 0); // POST: found should be either 1 or 0
    }
    
    return 0;
}