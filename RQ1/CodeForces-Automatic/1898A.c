#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    long long TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: 1 <= t <= 500
    while (TC--)
    {
        long long n, k;
        char s[101];
        scanf("%lld %lld %s", &n, &k, s);
        assert(n >= 3 && n <= 100); // PRE: 3 <= n <= 100
        assert(k >= 0 && k <= n); // PRE: 0 <= k <= n

        long long ct = 0;
        for (long long i = 0; i < n; ++i)
        {
            if (s[i] == 'B')
                ct++;
        }

        // POST: Count of 'B's in the final string is k
        if (ct == k)
        {
            printf("0\n");
            continue;
        }

        if (ct > k)
        {
            long long ctb = 0;
            for (long long i = 0; i < n; ++i)
            {
                if (s[i] == 'B')
                    ctb++;
                if (ctb == ct - k)
                {
                    printf("1\n%lld A\n", i + 1);
                    assert(ct - k == 1); // POST: The count of 'B's is reduced to k
                    break;
                }
            }
        }
        else
        {
            long long cta = 0;
            for (long long i = 0; i < n; ++i)
            {
                if (s[i] == 'A')
                    cta++;
                if (cta == k - ct)
                {
                    printf("1\n%lld B\n", i + 1);
                    assert(k - ct == 1); // POST: The count of 'B's is increased to k
                    break;
                }
            }
        }
    }
    return 0;
}