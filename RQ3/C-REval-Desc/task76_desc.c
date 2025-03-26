#include <stdio.h>

int func(int _result);

int get_max_triples(int n) {
    int A[n];
    int ans = 0;

    for (int i = 0; i < n; i++) {
        A[i] = (i + 1) * (i + 1) - (i + 1) + 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((A[i] + A[j] + A[k]) % 3 == 0) {
                    ans++;
                }
            }
        }
    }

    int _result = ans;
    return func(_result);
}