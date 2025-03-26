#include <stdio.h>
#include <assert.h>

int is_lucky(int num) {
    while (num > 0) {
        int r = num % 10;
        if (r != 4 && r != 7) {
            return 0;
        }
        num = num / 10;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000); // PRE: n is within the range 1 to 1000

    for (int num = 1; num <= 1000; ++num) {
        if (is_lucky(num) && n % num == 0) {
            printf("YES\n");
            assert(n % num == 0); // POST: n is almost lucky since n is divisible by lucky number
            return 0;
        }
    }
    printf("NO\n");
    assert(n % 1 != 0); // POST: If "NO" printed, n is not almost lucky
    return 0;
}