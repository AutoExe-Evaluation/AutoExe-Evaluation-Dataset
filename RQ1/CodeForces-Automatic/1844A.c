#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 100); // PRE: Number of test cases must be between 1 and 100
    while (TC--) 
    {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        assert(a >= 1 && a < b && b <= 100); // PRE: a must be less than b and in the range [1, 100]
        printf("%lld\n", a + b);
        assert(a + b >= 2 && a + b <= 200); // POST: The result n must be a positive integer in range [2, 200]
    }
    return 0;
}