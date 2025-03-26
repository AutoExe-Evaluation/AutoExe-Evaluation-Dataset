#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 5940); // PRE: Number of test cases is within the valid range.
    
    while (TCS--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        assert(a >= 1 && a <= 12); // PRE: 'a' is within the valid range.
        assert(b >= 1 && b <= 12); // PRE: 'b' is within the valid range.
        assert(c >= 1 && c <= 12); // PRE: 'c' is within the valid range.
        assert(d >= 1 && d <= 12); // PRE: 'd' is within the valid range.
        assert(a != b && a != c && a != d && b != c && b != d); // PRE: All numbers are distinct.
        
        int ct = 0;
        for (int i = (a < b ? a : b); i <= (a > b ? a : b); ++i) {
            if (i == c || i == d) ct++;
        }
        
        if (ct & 1) printf("YES\n");
        else printf("NO\n");
    }

    // POST: All test cases have been processed correctly, and the output is complete.
    return 0;
}