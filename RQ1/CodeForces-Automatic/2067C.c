#include <stdio.h>
#include <assert.h>

long long pre[9][1000]; // Adjusted size to hold results
int size_pre[9];

void gen(int start, int ct, int k, long long curr, long long *v, int sz) {
    if (ct == k) {
        pre[k][size_pre[k]] = curr;
        size_pre[k]++;
        return;
    }
    for (int i = start; i < sz; i++)
        gen(i, ct + 1, k, curr + v[i], v, sz);
}

void precom() {
    long long v[10];
    int idx = 0;
    for (long long i = 9; i <= 1e9; i = i * 10 + 9)
        v[idx++] = i;

    for (int k = 1; k <= 8; k++) {
        gen(0, 0, k, 0, v, idx);
    }
}

int has7(long long n) {
    while (n) {
        int r = n % 10;
        n /= 10;
        if (r == 7) return 1;
    }
    return 0;
}

int main() {
    precom(); 
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases should be in the range 1 to 10^4
    for (int TC = 1; TC <= TCS; ++TC) {
        long long n;
        scanf("%lld", &n);
        assert(n >= 10 && n <= 1000000000); // PRE: n should be in the range 10 to 10^9
        
        if (has7(n)) {
            printf("0\n");
            continue;
        }
        
        for (int k = 1; k <= 8; k++) {
            for (int j = 0; j < size_pre[k]; j++) {
                if (has7(n + pre[k][j])) {
                    printf("%d\n", k);
                    assert(has7(n + pre[k][j])); // POST: n + pre[k][j] should contain the digit 7
                    break;
                }
            }
        }
    }
    return 0;
}