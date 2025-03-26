#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 101

int min_length(char s[]) {
    int length = strlen(s);
    for (int i = 1; i < length; ++i) {
        if (s[i] == s[i - 1]) {
            return 1; // POST: If any two adjacent characters are equal, min length is 1
        }
    }
    return length; // POST: If all characters are unique, min length is the original length
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases must be within [1, 100]
    
    for (int TC = 1; TC <= TCS; ++TC) {
        char s[MAX_LEN];
        scanf("%s", s);
        assert(strlen(s) >= 1 && strlen(s) <= 100); // PRE: Length of string must be within [1, 100]
        
        int result = min_length(s);
        printf("%d\n", result);
    }
    return 0;
}