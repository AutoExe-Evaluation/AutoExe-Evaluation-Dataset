#include <stdio.h>
#include <string.h>
#include <ctype.h>

void solve(char *s) {
    int flg = 0;
    int idx = 0;
    char new_str[1000];
    strcpy(new_str, s);
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (isalpha(s[i])) {
            new_str[idx] = islower(s[i]) ? toupper(s[i]) : tolower(s[i]);
            flg = 1;
            idx++;
        } else {
            new_str[idx] = s[i];
            idx++;
        }
    }
    new_str[idx] = '\0';

    if (flg == 0) {
        char _result[1000];
        for (int i = 0; i < len; i++) {
            _result[i] = new_str[len - 1 - i];
        }
        _result[len] = '\0';
        assert(func(_result));
    } else {
        assert(func(new_str));
    }
}