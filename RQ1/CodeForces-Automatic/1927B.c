#include <stdio.h>
#include <string.h>
#include <map>
#include <assert.h>

#define int long long
#define pb push_back

int main() {
    int TC = 1; 
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases constraints

    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of the lost string constraints
        int a[200001];

        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            assert(a[i] >= 0 && a[i] < n); // PRE: Trace array values constraints
        }

        char s[200001];
        std::map<char, int> m;
        char c = 'a';
        int k = 0;

        for (int i = 0; i < n; ++i) {
            int x = a[i];
            if (x == 0) {
                s[k++] = c;
                m[c]++;
                c++;
            } else {
                for (auto it = m.begin(); it != m.end(); ++it) {
                    if (it->second == x) {
                        s[k++] = it->first;
                        m[it->first]++;
                        break;
                    }
                }
            }
        }
        s[k] = '\0';
        printf("%s\n", s);
        assert(k == n); // POST: Output string length matches input length
    }
}