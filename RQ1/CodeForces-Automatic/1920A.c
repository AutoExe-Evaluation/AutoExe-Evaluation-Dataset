#include <stdio.h>
#include <limits.h>
#include <vector>
#include <cassert>

#define int long long

int main() {
    int TC = 0;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 500); // PRE: number of test cases is within constraints

    while (TC--) {
        int n = 0;
        scanf("%lld", &n);
        assert(n >= 2 && n <= 100); // PRE: number of constraints is within constraints

        std::vector<int> v;
        int mn = 0, mx = INT_MAX;

        for (int i = 0; i < n; ++i) {
            int t = 0, x = 0;
            scanf("%lld %lld", &t, &x);
            assert(x >= 1 && x <= 1000000000); // PRE: x is within limits
            assert(t >= 1 && t <= 3); // PRE: type of constraint is valid
            
            if (t == 1)
                mn = (mn > x) ? mn : x;
            else if (t == 2)
                mx = (mx < x) ? mx : x;
            else
                v.push_back(x);
        }

        int ans = mx - mn;
        if (ans < 0) {
            printf("0\n");
            assert(ans + 1 == 0); // POST: no valid integers in case of negative range
            continue;
        }

        for (size_t j = 0; j < v.size(); j++) {
            if (v[j] >= mn && v[j] <= mx)
                ans--;
        }

        printf("%lld\n", ans + 1);
        assert(ans + 1 >= 0); // POST: number of valid integers is non-negative
    }
    return 0;
}