#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: number of test cases should be within bounds
    while(TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: number of queries should be within bounds
        int *v = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 0 && v[i] <= 1000000000); // PRE: each element should be within bounds
        }
        
        char *s = (char *)malloc((n + 1) * sizeof(char));
        s[0] = '1';
        s[n] = '\0';
        
        int last = v[0];
        int increase = 1;
        for(int i = 1; i < n; ++i) {
            if(v[i] >= last && increase) {
                s[i] = '1';
                last = v[i];
            }
            else if(v[i] < last && v[0] >= v[i] && increase) {
                increase = 0;
                last = v[i];
                s[i] = '1';
            }
            else if(v[i] >= last && v[i] <= v[0]) {
                last = v[i];
                s[i] = '1';
            }
            else {
                s[i] = '0';
            }
        }
        printf("%s\n", s);
        
        free(v);
        free(s);
        assert(s[0] == '1'); // POST: The first character should always be '1'
    }
    return 0;
}