#include <stdio.h>
#include <assert.h>

int main()
{
    long long TCS;
    scanf("%lld", &TCS);
    assert(TCS >= 1 && TCS <= 500); // PRE: Number of test cases should be in the range [1, 500]
    
    for (long long TC = 1; TC <= TCS; ++TC)
    {
        long long a, b, d, e;
        scanf("%lld %lld %lld %lld", &a, &b, &d, &e);
        assert(a >= 1 && a <= 100); // PRE: a_1 should be in the range [1, 100]
        assert(b >= 1 && b <= 100); // PRE: a_2 should be in the range [1, 100]
        assert(d >= 1 && d <= 100); // PRE: a_4 should be in the range [1, 100]
        assert(e >= 1 && e <= 100); // PRE: a_5 should be in the range [1, 100]
        
        long long c1 = a + b;
        long long c2 = d - b;
        long long c3 = e - d;
        
        long long fibonacciness;
        
        if (c1 == c2 && c2 == c3)
            fibonacciness = 3;
        else if (c1 == c2 || c2 == c3 || c1 == c3)
            fibonacciness = 2;
        else
            fibonacciness = 1;
        
        printf("%lld\n", fibonacciness);
        assert(fibonacciness >= 1 && fibonacciness <= 3); // POST: Fibonacciness should be in the range [1, 3]
    }
    
    return 0;
}