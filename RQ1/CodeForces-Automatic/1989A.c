#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 500); // PRE: 1 ≤ n ≤ 500
    for(int i = 0; i < n; ++i)
    {
        int x, y;
        scanf("%lld %lld", &x, &y);
        assert(y >= -50 && y <= 50); // PRE: -50 ≤ y ≤ 50
        assert(x >= -50 && x <= 50); // PRE: -50 ≤ x ≤ 50
        if(y >= -1) 
            printf("YES\n");
        else 
            printf("NO\n");
    }
    // POST: output "YES" if y >= -1, otherwise "NO"
    return 0;
}