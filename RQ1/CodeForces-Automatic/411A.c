#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char s[101];
    scanf("%s", s);
    
    assert(strlen(s) >= 5); // PRE: Password length must be at least 5 characters
    int flag1 = 0, flag2 = 0, flag3 = 0;
    
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z' && flag1 == 0) {
            flag1 = 1;
        } else if (s[i] >= 'a' && s[i] <= 'z' && flag2 == 0) {
            flag2 = 1;
        } else if (s[i] >= '0' && s[i] <= '9' && flag3 == 0) {
            flag3 = 1;
        }
        if (flag1 == 1 && flag2 == 1 && flag3 == 1) {
            break;
        }
    }

    assert(flag1 == 1 && flag2 == 1 && flag3 == 1); // POST: Password must contain at least one uppercase letter, one lowercase letter, and one digit

    if (flag1 == 1 && flag2 == 1 && flag3 == 1) {
        printf("Correct");
    } else {
        printf("Too weak");
    }
    
    return 0;
}