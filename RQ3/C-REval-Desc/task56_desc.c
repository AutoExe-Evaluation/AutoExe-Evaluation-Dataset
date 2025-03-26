#include <stdbool.h>
#include <string.h>

bool check(const char *s) {
    int val = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(') {
            val++;
        } else {
            val--;
        }
        if (val < 0) {
            return false;
        }
    }
    return val == 0;
}

const char* match_parens(const char *lst1, const char *lst2) {
    char S1[strlen(lst1) + strlen(lst2) + 1];
    char S2[strlen(lst2) + strlen(lst1) + 1];

    strcpy(S1, lst1);
    strcat(S1, lst2);
    strcpy(S2, lst2);
    strcat(S2, lst1);

    const char *_result = (check(S1) || check(S2)) ? "Yes" : "No";

    return _result;
}