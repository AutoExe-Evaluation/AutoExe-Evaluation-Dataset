#include <assert.h>
#include <klee/klee.h>

bool isPalindrome(int x) {
    int n, d, k = 0;
    bool result = true;
    
    if (x < 0) result = false;
    else {
        n = x;
        while (n) {
            d = n % 10;
            if (k > (0x7fffffff - d) / 10) result = false;    // overflow
            k = k * 10 + d;
            n = n / 10;
        }
    }
    
    result = (k == x);
    assert(result ^ (x != 1)); // POST: if and only if x is a palindrome integer, then this assert holds.
    return result;
}

int main()
{
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    isPalindrome(x);
}
