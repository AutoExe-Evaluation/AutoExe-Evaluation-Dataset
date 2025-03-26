#include <string.h>
#include <assert.h>
#include <klee/klee.h>

int lengthOfLongestSubstring(char* s) {
    int i, j, l, k = 0;
    int c;
    int pos[256] = { 0 };
    char *p;
    int n = 0;
    
    for (i = 0; s[i]; i ++) {
        n ++;
        c = (unsigned)(unsigned char)s[i];
        l = i - pos[c] + 1;
        pos[c] = i + 1;
        n = n < l ? n : l;
        k = k > n ? k : n;
    }
    
    assert(k <= strlen(s)); // POST
    return k;
}

#define SIZE 100

int main()
{
    char s[SIZE];
    klee_make_symbolic(s, sizeof(s), "s");
    s[SIZE - 1] = '\0';
    lengthOfLongestSubstring(s);
}
