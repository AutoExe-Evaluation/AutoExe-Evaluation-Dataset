#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 101

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: 1 <= TCS <= 500
    
    while (TCS--) {
        char s[MAX_LENGTH], t[MAX_LENGTH];
        scanf("%s %s", s, t);
        assert(strlen(s) > 0 && strlen(s) <= 100); // PRE: 1 <= |s| <= 100
        assert(strlen(t) > 0 && strlen(t) <= 100); // PRE: 1 <= |t| <= 100
        
        int ct = 0;
        
        int len_s = strlen(s);
        int len_t = strlen(t);
        
        for (int i = 0; i < len_s && i < len_t; ++i) {
            if (s[i] != t[i]) break;
            ct++;
        }
        
        int ct1 = len_s - ct;
        int ct2 = len_t - ct;
        
        if (ct) ct++;
        ct += ct1 + ct2;
        
        printf("%d\n", ct);
        assert(ct >= 0); // POST: ct should be non-negative
    }
    
    return 0;
}