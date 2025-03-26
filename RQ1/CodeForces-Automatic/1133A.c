#include <stdio.h>
#include <assert.h>

int main()
{
    char s[6], e[6];
    scanf("%s %s", s, e);
    int h1 = (s[0] - '0') * 10 + (s[1] - '0');
    int m1 = (s[3] - '0') * 10 + (s[4] - '0');
    int h2 = (e[0] - '0') * 10 + (e[1] - '0');
    int m2 = (e[3] - '0') * 10 + (e[4] - '0');
    
    assert(h1 >= 0 && h1 <= 23 && m1 >= 0 && m1 <= 59); // PRE: start time is valid
    assert(h2 >= 0 && h2 <= 23 && m2 >= 0 && m2 <= 59); // PRE: end time is valid
    assert((m1 % 2 == m2 % 2) && ((h2 * 60 + m2) - (h1 * 60 + m1) >= 2)); // PRE: contest duration conditions

    int t1 = h1 * 60 + m1;
    int t2 = h2 * 60 + m2;
    int t = (t1 + t2) / 2;
    int h = t / 60;
    int m = t % 60;

    printf("%02d:%02d\n", h, m);
    
    assert(h >= 0 && h <= 23 && m >= 0 && m <= 59); // POST: midpoint time is valid
    return 0;
}