#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int v[3];
    for(int i = 0; i < 3; ++i)
        scanf("%lld", &v[i]);

    // PRE: Ensure that input values are non-negative integers within the specified range
    assert(v[0] >= 0 && v[0] <= 2e9);
    assert(v[1] >= 0 && v[1] <= 2e9);
    assert(v[2] >= 0 && v[2] <= 2e9);

    // Sorting v array
    for(int i = 0; i < 2; ++i)
    {
        for(int j = i + 1; j < 3; ++j)
        {
            if(v[i] > v[j])
            {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    int max_tables = (v[0] + v[1] < (v[0] + v[1] + v[2]) / 3) ? v[0] + v[1] : (v[0] + v[1] + v[2]) / 3;

    // POST: The number of tables that can be decorated must be non-negative and 
    // must not exceed a third of the total number of balloons
    assert(max_tables >= 0);
    assert(max_tables <= (v[0] + v[1] + v[2]) / 3);

    printf("%lld\n", max_tables);
    return 0;
}