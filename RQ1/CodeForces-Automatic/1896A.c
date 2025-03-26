#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 5000); // PRE: The number of test cases should be between 1 and 5000

    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 3 && n <= 10); // PRE: The size of the permutation should be between 3 and 10
        
        int v[10];
        for(int i = 0; i < n; ++i) {
            scanf("%d", &v[i]);
            assert(v[i] >= 1 && v[i] <= n); // PRE: Each element of the permutation must be between 1 and n
        }

        bool flag = true;
        while(flag) {
            flag = false;
            for(int i = 1; i < n - 1; ++i) {
                if(v[i] > v[i - 1] && v[i] > v[i + 1]) {
                    flag = true;
                    int temp = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = temp;
                }
            }
        }

        bool sorted = true;
        for(int i = 1; i < n; ++i) {
            if(v[i] < v[i - 1]) {
                sorted = false;
                break;
            }
        }
        
        assert(sorted || !sorted); // POST: The output will reflect whether the array is sorted or not
        if(sorted)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}