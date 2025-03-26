#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 1000); // PRE: number of test cases must be in the valid range
    
    for (int TC = 1; TC <= TCS; ++TC) {
        char s[11];
        scanf("%s", s);
        int len = strlen(s);
        assert(len >= 1 && len <= 10); // PRE: length of string must be in the valid range
        
        for (int i = 1; i < len; ++i) {
            if (s[i] == s[i - 1]) {
                if (s[i] == 'a') {
                    for (int j = len; j > i; --j) {
                        s[j + 1] = s[j];
                    }
                    s[i] = 'b';
                    s[len + 1] = '\0';
                    printf("%s\n", s);
                    assert(strlen(s) == len + 1); // POST: length of the new string should be original length + 1
                    break;
                } else {
                    for (int j = len; j > i; --j) {
                        s[j + 1] = s[j];
                    }
                    s[i] = 'a';
                    s[len + 1] = '\0';
                    printf("%s\n", s);
                    assert(strlen(s) == len + 1); // POST: length of the new string should be original length + 1
                    break;
                }
            }
        }
        if (s[len - 1] == 'a') {
            s[len] = 'b';
            s[len + 1] = '\0';
        } else {
            s[len] = 'a';
            s[len + 1] = '\0';
        }
        printf("%s\n", s);
        assert(strlen(s) == len + 1); // POST: length of the new string should be original length + 1
    }
    return 0;
}