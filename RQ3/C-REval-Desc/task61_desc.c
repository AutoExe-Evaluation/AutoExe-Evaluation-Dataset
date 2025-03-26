#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int func(int *result, int k);

int* minPath(int** grid, int k, int n) {
    int val = n * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int temp[4], count = 0;
                if (i != 0) temp[count++] = grid[i - 1][j];
                if (j != 0) temp[count++] = grid[i][j - 1];
                if (i != n - 1) temp[count++] = grid[i + 1][j];
                if (j != n - 1) temp[count++] = grid[i][j + 1];
                for (int x = 0; x < count; x++) {
                    if (temp[x] < val) {
                        val = temp[x];
                    }
                }
            }
        }
    }

    int* ans = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        if (i % 2 == 0) {
            ans[i] = 1;
        } else {
            ans[i] = val;
        }
    }

    assert(func(ans, k));
    return ans;
}