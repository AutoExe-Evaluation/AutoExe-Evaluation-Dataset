#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 2 && n <= 200); // PRE: n is between 2 and 200 inclusive
    
    char s[201];
    scanf("%s", s);
    assert(strlen(s) == n); // PRE: The length of the string matches n
    
    long long ctL = 0, ctO = 0, netL = 0, netO = 0;

    for (long long i = 0; i < n; i++) {
        if (s[i] == 'L')
            netL++;
        else
            netO++;
    }

    for (long long i = 0; i < n - 1; i++) {
        if (s[i] == 'L')
            ctL++;
        else
            ctO++;

        if (ctL != netL - ctL && ctO != netO - ctO) {
            printf("%lld\n", i + 1);
            assert(ctL > 0 && ctO > 0); // POST: Ensures both counts are positive
            assert(netL - ctL > 0 && netO - ctO > 0); // POST: Ensures remaining counts are positive
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}