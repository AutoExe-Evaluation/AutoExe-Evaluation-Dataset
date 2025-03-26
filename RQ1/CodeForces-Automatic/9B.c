#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>

int main() {
    long long n, b, s;
    scanf("%lld %lld %lld", &n, &b, &s);
    assert(n >= 2 && n <= 100); // PRE: 2 ≤ n ≤ 100
    assert(b >= 1 && b <= 1000); // PRE: 1 ≤ vb ≤ 1000
    assert(s >= 1 && s <= 1000); // PRE: 1 ≤ vs ≤ 1000

    long long v[n];
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
    }

    long long fs, fy;
    scanf("%lld %lld", &fs, &fy);

    double mn = DBL_MAX;
    long long ans = -1;

    for (long long i = 1; i < n; i++) {
        double t1 = (double)v[i] / b;
        double d = sqrt(pow(fs - v[i], 2) + pow(fy, 2));
        double t2 = d / s;

        double t = t1 + t2;
        if (t < mn - 1e-8) {
            ans = i + 1;
            mn = t;
        } else if (fabs(t - mn) < 1e-8) {
            double pre = sqrt(pow(fs - v[ans - 1], 2) + pow(fy, 2));
            if (d < pre) {
                ans = i + 1;
                mn = t;
            }
        }
    }

    printf("%lld\n", ans);
    assert(ans >= 1 && ans <= n); // POST: 1 ≤ ans ≤ n
    return 0;
}