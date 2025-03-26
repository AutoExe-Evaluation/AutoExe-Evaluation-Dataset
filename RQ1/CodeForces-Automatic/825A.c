#include <stdio.h>
#include <assert.h>

int main()
{
    long long n;
    char s[90];
    scanf("%lld %s", &n, s);
    assert(n >= 1 && n <= 89); // PRE: Length of the string should be within valid range

    long long ct = 0;
    long long decodedNumber = 0;
    for (long long i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            decodedNumber = decodedNumber * 10 + ct;
            ct = 0;
            continue;
        }
        ct++;
    }
    decodedNumber = decodedNumber * 10 + ct; // Handle the last segment
    printf("%lld\n", decodedNumber);
    
    assert(decodedNumber > 0 && decodedNumber <= 1e9); // POST: Decoded number must be positive and <= 10^9
    return 0;
}