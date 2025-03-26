#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[106];
    scanf("%s", s);
    int length = strlen(s);
    
    assert(length > 0 && length <= 105); // PRE: 0 ≤ n ≤ 10^105

    if (length < 2) {
        int n = s[0] - '0';
        if (n % 4)
            printf("0\n");
        else
            printf("4\n");
        assert(n >= 0 && n <= 9); // POST: result is correct for n < 10
        return 0;
    }
    
    char str[3];
    strncpy(str, s + length - 2, 2);
    str[2] = '\0';
    int n = atoi(str);
    if (n % 4)
        printf("0\n");
    else
        printf("4\n");

    assert(n >= 0 && n <= 99); // POST: result is correct for n >= 10, based on last two digits
    return 0;
}