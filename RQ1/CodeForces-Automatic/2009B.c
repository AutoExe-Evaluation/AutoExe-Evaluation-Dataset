#include <stdio.h>
#include <assert.h>

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 100); // PRE: 1 ≤ t ≤ 100
    
    for (int TC = 1; TC <= TCS; ++TC) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 500); // PRE: 1 ≤ n ≤ 500
        int v[500], index = 0;
        
        for (int i = 0; i < n; ++i) {
            char s[5];
            scanf("%s", s);
            int found = 0;
            for (int j = 0; j < 4; ++j) {
                if (s[j] == '#') {
                    v[index++] = j + 1;
                    found = 1;
                }
            }
            assert(found); // PRE: There must be exactly one '#'
        }
        
        for (int i = index - 1; i >= 0; --i) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
    assert(TCS * 500 >= 1 && TCS * 500 <= 500); // POST: summed n over all test cases does not exceed 500
    return 0;
}