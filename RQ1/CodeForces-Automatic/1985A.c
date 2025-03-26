#include <stdio.h>
#include <assert.h>

int main()
{
    int TCS = 1;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: Number of test cases must be between 1 and 100
    for (int TC = 1; TC <= TCS; ++TC)
    {
        char a[4], b[4];
        scanf("%s %s", a, b);
        assert(strlen(a) == 3 && strlen(b) == 3); // PRE: Both strings must be of length 3
        
        char temp = a[0];
        a[0] = b[0];
        b[0] = temp;
        
        printf("%s %s\n", a, b);
        assert(strlen(a) == 3 && strlen(b) == 3); // POST: Both strings' lengths remain 3 after swap
    }
    return 0;
}