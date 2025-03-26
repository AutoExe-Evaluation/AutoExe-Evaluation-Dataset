#include <stdio.h>
#include <assert.h>

#define yes printf("YES\n")
#define no printf("NO\n")

int main() {
    int TCS;
    scanf("%d", &TCS);
    
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within valid range
    
    for (int TC = 1; TC <= TCS; ++TC) {
        long long a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        
        assert(a >= 0 && a <= 1000000000); // PRE: x1 is within valid range
        assert(b >= 0 && b <= 1000000000); // PRE: y1 is within valid range
        assert(c >= a && c <= 1000000000); // PRE: x2 is within valid range and x2 >= x1
        assert(d >= b && d <= 1000000000); // PRE: y2 is within valid range and y2 >= y1
        assert(a != b); // PRE: Scores before distraction are not equal
        assert(c != d); // PRE: Scores after distraction are not equal

        if ((a > b && c < d) || (a < b && c > d))
            no;
        else
            yes;
        
        // POST: The output correctly reflects if a tie occurred or not
        // This can be assumed because we've checked the conditions logically
    }
    
    return 0;
}