#include <stdio.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 2 && n <= 9); // PRE: n is between 2 and 9 inclusive
    n++;

    for (int i = 1; i <= n; ++i) {
        int p = 0;
        for (int j = i; j < n; ++j)
            printf("  ");

        for (int j = 0; j < i - 1; ++j) {
            printf("%d", p++);
            if (j + 1 < i)
                printf(" ");
        }
        for (int j = 0; j < i; ++j) {
            printf("%d", p--);
            if (j + 1 < i)
                printf(" ");
        }
        printf("\n");
    }
    
    n--;
    
    for (int i = 0; i <= n; ++i) {
        int p = 0;
        for (int j = 0; j <= i; ++j)
            printf("  ");
        
        for (int j = i; j < n - 1; ++j) {
            printf("%d", p++);
            if (j + 1 < n)
                printf(" ");
        }
        for (int j = i; j < n; ++j) {
            printf("%d", p--);
            if (j + 1 < n)
                printf(" ");
        }
        printf("\n");
    }
    
    assert(n >= 1); // POST: n is reduced by 1 and still valid
    return 0;
}