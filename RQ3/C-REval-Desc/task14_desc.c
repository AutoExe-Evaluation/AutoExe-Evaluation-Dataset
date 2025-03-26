#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(int num);

void fizz_buzz(int n) {
    int *ns = (int *)malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (i % 11 == 0 || i % 13 == 0) {
            ns[count++] = i;
        }
    }

    char s[100] = "";
    for (int i = 0; i < count; i++) {
        char buffer[12];
        sprintf(buffer, "%d", ns[i]);
        strcat(s, buffer);
    }

    int ans = 0;
    for (int i = 0; i < strlen(s); i++) {
        ans += (s[i] == '7');
    }

    int _result = ans;

    free(ns);
    if (!func(_result)) {
        exit(1);
    }
}