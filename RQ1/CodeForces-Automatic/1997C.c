#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200000

long long pow(long long x, long long y, long long m) {
    long long ans = 1;
    x %= m;
    while(y) {
        if(y & 1) ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 5000); // PRE: 1 ≤ t ≤ 5000
    while (TCS--) {
        int n;
        char s[MAX];
        scanf("%d %s", &n, s);
        assert(n >= 2 && n <= 200000 && n % 2 == 0); // PRE: 2 ≤ n ≤ 2 * 10^5, n is even
        
        long long ct = 0, cost = 0;
        int v[MAX], top = -1;

        for(int i = 0; i < n; ++i) {
            if(s[i] == '(') {
                ct++;
                v[++top] = i;
            } else if(s[i] == ')') {
                ct--;
                if (top >= 0) cost += i - v[top]; // Ensure we don't access an empty stack
                top--;
            } else {
                if(ct) {
                    ct--;
                    if (top >= 0) cost += i - v[top]; // Ensure we don't access an empty stack
                    top--;
                } else {
                    ct++;
                    v[++top] = i;
                }
            }
        }
        printf("%lld\n", cost);
        assert(cost >= 0); // POST: The cost must be non-negative
    }
    return 0;
}