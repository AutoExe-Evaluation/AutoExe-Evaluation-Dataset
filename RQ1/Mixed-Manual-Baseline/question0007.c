#include <assert.h>
#include <klee/klee.h>

int reverse(int x) {
    assert (x > 0); // PRE
    int d, k = 0;
    while (x) {
        d = x % 10;
        if ((x > 0 && k > (0x7fffffff - d) / 10) ||
            (x < 0 && k < ((signed)0x80000000 - d) / 10)) {
            return 0;   // overflow
        }
        k = k * 10 + d;
        x = x / 10;
    }
    assert(k >= x); // POST
    return k;
}

int main()
{
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    klee_assume(x > 0);
    reverse(x);
}
