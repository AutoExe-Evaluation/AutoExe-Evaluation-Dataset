#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define int long long

int cmp(const void *a, const void *b) {
    if (*(char *)a == *(char *)b) {
        return 0;
    }
    return (*(char *)a < *(char *)b) ? 1 : -1;
}

int main() {
    int TC;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases must be in the range [1, 10000]
    
    while (TC--) {
        int n;
        scanf("%lld", &n);
        assert(n >= 1 && n <= 200000); // PRE: Length of the string must be in the range [1, 200000]
        
        char *s = (char *)malloc((n + 1) * sizeof(char));
        scanf("%s", s);
        assert(strlen(s) == n); // PRE: Length of the input string should match the specified length

        int *v = (int *)malloc(n * sizeof(int));
        int v_index = 0;

        for (int i = 0; i < n; ++i) {
            while (v_index > 0 && s[v[v_index - 1]] < s[i]) {
                v_index--;
            }
            v[v_index++] = i;
        }

        int ct = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == s[v[0]]) {
                ct++;
            }
        }

        for (int i = 0; i < v_index / 2; ++i) {
            char temp = s[v[i]];
            s[v[i]] = s[v[v_index - 1 - i]];
            s[v[v_index - 1 - i]] = temp;
        }

        int sorted = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] < s[i - 1]) {
                sorted = 0;
                break;
            }
        }

        if (sorted) {
            printf("%lld\n", v_index - ct);
            assert(v_index - ct >= 0); // POST: The number of operations should not be negative
        } else {
            printf("-1\n");
            assert(1); // POST: If it's impossible to sort, -1 should be printed
        }

        free(s);
        free(v);
    }
    return 0;
}