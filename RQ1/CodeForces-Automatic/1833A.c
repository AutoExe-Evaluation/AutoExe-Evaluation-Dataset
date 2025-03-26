#include <stdio.h>
#include <string.h>
#include <set>
#include <assert.h>

#define int long long

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: 1 ≤ t ≤ 10^4
    while (TC--) {
        int n;
        char s[51];
        scanf("%lld %s", &n, s);
        assert(n >= 2 && n <= 50); // PRE: 2 ≤ n ≤ 50
        std::set<char[3]> st;
        for (int i = 0; i < n - 1; ++i) {
            char str[3];
            str[0] = s[i];
            str[1] = s[i + 1];
            str[2] = '\0';
            st.insert(str);
        }
        printf("%lld\n", (long long)st.size());
        assert(st.size() >= 1 && st.size() <= 50); // POST: The number of distinct pairs should be valid based on string length.
    }
    return 0;
}