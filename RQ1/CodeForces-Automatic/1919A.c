#include <stdio.h>
#include <assert.h>

#define int long long

int main()
{
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: 1 ≤ t ≤ 1000

    while (TC--)
    {
        int a, b;
        scanf("%lld%lld", &a, &b);
        assert(a >= 1 && a <= 1000000000); // PRE: 1 ≤ a ≤ 10^9
        assert(b >= 1 && b <= 1000000000); // PRE: 1 ≤ b ≤ 10^9

        if ((a + b) & 1)
            printf("Alice\n");
        else
            printf("Bob\n");

        // POST: Ensure the output is correct based on the sum of a and b
        assert(((a + b) & 1 && !((a + b) % 2 == 0)) || (!(a + b) & 1 && ((a + b) % 2 == 0))); // Alice wins if sum is odd, Bob if even
    }
    return 0;
}