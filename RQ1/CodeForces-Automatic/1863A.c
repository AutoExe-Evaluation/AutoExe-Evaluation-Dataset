#include<stdio.h>
#include<assert.h>

int main()
{
    long long t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 500); // PRE: number of test cases should be within specified limits
    
    while (t--)
    {
        long long n, a, q;
        char s[101];
        scanf("%lld%lld%lld%s", &n, &a, &q, s);
        assert(n >= 1 && n <= 100); // PRE: number of subscribers should be within specified limits
        assert(a >= 0 && a <= n);   // PRE: number of online subscribers should be within specified limits
        assert(q >= 1 && q <= 100);  // PRE: number of notifications should be within specified limits
        
        long long x = 0, y = 0;

        for(int i = 0; i < q; i++)
        {
            if(s[i] == '+') 
                x++;
            else
                y++;
            
            if (a + x - y >= n)
            {
                printf("YES\n");
                assert(a + x - y >= n); // POST: All subscribers have necessarily read the post
                break;
            }
        }
        
        if (a + x - y >= n || a >= n)
        {
            printf("YES\n");
            assert(a + x - y >= n || a >= n); // POST: All subscribers have necessarily read the post
        }
        else if(a + x >= n)
        {
            printf("MAYBE\n");
            assert(a + x >= n); // POST: It is possible that all subscribers have read the post
        }
        else
        {
            printf("NO\n");
            assert(a + x < n); // POST: It is impossible for all subscribers to have read the post
        }
    }
    
    return 0;
}