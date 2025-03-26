#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100000); // PRE: 1 <= TCS <= 100000

    while (TCS--) {
        int n;
        scanf("%d", &n);
        assert(n >= 2 && n <= 200000); // PRE: 2 <= n <= 200000
        int v[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert((v[i] == -1) || (1 <= v[i] && v[i] <= 100000000)); // PRE: -1 or 1 <= v_i <= 10^8
        }

        int prev = -1;
        for (int i = 0; i < n; ++i) {
            if (v[i] == -1) continue;
            if (prev == -1) {
                for (int j = i - 1; j >= 0; --j) {
                    if (v[j + 1] > 1) v[j] = v[j + 1] / 2;
                    else v[j] = v[j + 1] * 2;
                }
                prev = i;
                continue;
            }
            int l = prev, r = i;
            while (r - l > 1) {
                if (v[r] > v[l]) {
                    v[r - 1] = v[r] / 2;
                    r--;
                } else {
                    if (v[l] > 1) v[l + 1] = v[l] / 2;
                    else v[l + 1] = v[l] * 2;
                    l++;
                }
            }
            prev = i;
        }
        if (prev < n - 1) {
            if (prev == -1) {
                v[0] = 1;
                prev = 0;
            }
            for (int i = prev + 1; i < n; ++i) {
                if (v[i - 1] > 1) v[i] = v[i - 1] / 2;
                else v[i] = v[i - 1] * 2;
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            if (v[i] != v[i + 1] / 2 && v[i + 1] != v[i] / 2) {
                printf("-1\n");
                return 0; // POST: output -1 if no valid sequence
            }
        }
        for (int i = 0; i < n; ++i) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
    return 0; // POST: valid sequence output
}