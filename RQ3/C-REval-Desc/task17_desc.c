#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* change_base(int x, int base) {
    char* ret = (char*)malloc(32); // Assumption: max digits will not exceed 32
    ret[0] = '\0';
    while (x > 0) {
        char buffer[2];
        sprintf(buffer, "%d", x % base);
        strcat(ret, buffer);
        x /= base;
    }
    // Reverse the string
    int len = strlen(ret);
    for (int i = 0; i < len / 2; i++) {
        char temp = ret[i];
        ret[i] = ret[len - i - 1];
        ret[len - i - 1] = temp;
    }
    assert(func(ret));
    return ret;
}