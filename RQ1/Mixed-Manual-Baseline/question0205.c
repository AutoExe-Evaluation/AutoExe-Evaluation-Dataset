#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <klee/klee.h>

bool isIsomorphic(char* s, char* t) {
    char a[256] = { 0 };
    char b[256] = { 0 };
    bool result = true;
    while (*s) {
        //printf("%c:%c\n", *s, *t);
        if (a[(unsigned char)*s] == 0 && b[(unsigned char)*t] == 0) {
            a[(unsigned char)*s] = *t;
            b[(unsigned char)*t] = *s;
        } else if (a[(unsigned char)*s] == *t && b[(unsigned char)*t] == *s) {
        } else {
            result = false;
            break;
        }
        s ++;
        t ++;
    }
    assert(!result || strlen(s) == strlen(t)); // POST
    return result;
}

#define SIZE 100

int main()
{
    char s[SIZE], t[SIZE];
    klee_make_symbolic(s, sizeof(s), "s");
    klee_make_symbolic(t, sizeof(t), "t");
    s[SIZE - 1] = '\0';
    t[SIZE - 1] = '\0';
    isIsomorphic(s, t);
}
