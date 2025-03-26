#include <stdio.h>
#include <assert.h>

int main()
{
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases is valid (1 ≤ t ≤ 10^4)

    while (TC--)
    {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 100000); // PRE: length of the sequence is valid (1 ≤ n ≤ 10^5)

        if (n % 2 == 0)
        {
            printf("1 3");
            for (int i = 1; i <= n - 2; ++i)
            {
                printf(" 2");
            }
            printf("\n");
        }
        else
        {
            for (int i = 1; i <= n; ++i)
            {
                printf("1 ");
            }
            printf("\n");
        }
    }

    return 0;
    // POST: a sequence was printed satisfying the conditions: 1 ≤ a_i ≤ 10^9 and a_1 ⊕ a_2 ⊕ ... ⊕ a_n = (a_1 + a_2 + ... + a_n) / n
}