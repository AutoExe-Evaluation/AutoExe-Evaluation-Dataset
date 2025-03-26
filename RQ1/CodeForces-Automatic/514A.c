#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[20];
    scanf("%s", s);
    
    // PRE: The input number x must be within the range 1 ≤ x ≤ 10^18
    assert(1 <= atoll(s) && atoll(s) <= 1000000000000000000); // PRE: 1 ≤ x ≤ 10^18
    
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int x = s[i] - '0';
        if (i == 0 && x == 9)
            continue;
        if (x >= 5)
            s[i] = '9' - x + '0';
    }
    
    // POST: The output number must be positive and shouldn't have leading zeros.
    assert(s[0] != '0'); // POST: No leading zero
    
    printf("%s\n", s);
    return 0;
}