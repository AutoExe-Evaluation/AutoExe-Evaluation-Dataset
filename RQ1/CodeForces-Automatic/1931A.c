#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int t;
    scanf("%lld", &t);
    assert(t >= 1 && t <= 100); // PRE: 1 <= t <= 100

    while (t--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 3 && n <= 78); // PRE: 3 <= n <= 78

        int first = (n - 52 > 0) ? n - 52 : 1;
        int second = (n - first - 26 > 0) ? n - first - 26 : 1;
        int third = (n - first - second > 0) ? n - first - second : 1;

        // Ensure the total encodes correctly
        assert(first + second + third == n); // POST: first + second + third == n

        printf("%c%c%c\n", first + 'a' - 1, second + 'a' - 1, third + 'a' - 1);
    }
    return 0;
}