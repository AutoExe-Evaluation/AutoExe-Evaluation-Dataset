#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 101

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases within bounds
    
    while (TCS--) {
        char a[MAX_LEN], b[MAX_LEN], c[MAX_LEN];
        scanf("%s %s %s", a, b, c);
        int len = strlen(a);
        
        assert(len > 0 && len <= 100); // PRE: Length of strings within bounds
        
        for (int i = 0; i < len; i++) {
            assert(a[i] >= 'a' && a[i] <= 'z'); // PRE: a[i] is lowercase
            assert(b[i] >= 'a' && b[i] <= 'z'); // PRE: b[i] is lowercase
            assert(c[i] >= 'a' && c[i] <= 'z'); // PRE: c[i] is lowercase
            
            if (a[i] != c[i] && b[i] != c[i]) {
                printf("NO\n");
                assert(0); // POST: impossible to make a equal to b
                break;
            }
        }
        
        printf("YES\n");
        assert(1); // POST: a can be made equal to b
    }
    return 0;
}