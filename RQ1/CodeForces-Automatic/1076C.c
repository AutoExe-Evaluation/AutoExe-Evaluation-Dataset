#include <stdio.h>
#include <math.h>
#include <assert.h>

int main()
{
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be between 1 and 1000
    
    while (TC--) 
    {
        double d;
        scanf("%lf", &d);
        assert(d >= 0 && d <= 1000); // PRE: d should be a non-negative integer not greater than 1000

        if (d == 0)
        {
            printf("Y %.9f %.9f\n", 0.0, 0.0);
            assert(fabs((0.0 + 0.0) - (0.0 * 0.0)) <= 1e-6); // POST: condition satisfied
            continue;
        }
        if (d < 4)
        {
            printf("N\n");
            continue;
        }
        
        double D = sqrt(d * d - 4 * d);
        double a = (d + D) / 2.0;
        double b = (d - D) / 2.0;
        printf("Y %.9f %.9f\n", a, b);
        
        assert(fabs((a + b) - (a * b)) <= 1e-6); // POST: condition satisfied
        assert(fabs((a + b) - d) <= 1e-6); // POST: condition satisfied
    }
    return 0;
}