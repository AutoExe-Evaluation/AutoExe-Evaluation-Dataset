#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <klee/klee.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

bool isOneEditDistance(char* s, char* t) {
    assert(abs(strlen(s) - strlen(t)) >= 2);
    int sl = strlen(s);
    int tl = strlen(t);
    int i, m;
    
    m = sl - tl;
    if (m > 1 || m < -1) return false;
    
    for (i = 0; i < sl && i < tl; i ++) {
        if (s[i] == t[i]) continue;
        if (!m) return !strcmp(&s[i + 1], &t[i + 1]);
        if (m > 0) return !strcmp(&s[i + 1], &t[i]);
        return !strcmp(&s[i], &t[i + 1]);
    }
    
    assert(m == 0); // POST
    return m == 0;
}

#define SIZE 100

int main()
{
    char s[SIZE], t[SIZE];
    klee_make_symbolic(s, sizeof(s), "s");
    klee_make_symbolic(t, sizeof(t), "t");
    isOneEditDistance(s, t);
}
