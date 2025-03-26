#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int ll;

struct map_entry {
    int key;
    int value;
};

int main() {
    int n;
    assert(scanf("%d", &n) == 1); // PRE: n must be read successfully
    assert(n >= 1 && n <= 200000); // PRE: n is within the constraints

    struct map_entry m[200001] = {0};
    int m_count = 0;

    for (int i = 0; i < n; i++) {
        int x;
        assert(scanf("%d", &x) == 1); // PRE: x must be read successfully
        assert(x >= 0 && x <= 200000); // PRE: x is within the constraints
        int found = 0;
        for (int j = 0; j < m_count; j++) {
            if (m[j].key == x) {
                m[j].value++;
                found = 1;
                break;
            }
        }
        if (!found) {
            m[m_count].key = x;
            m[m_count].value = 1;
            m_count++;
        }
    }
    
    if (n < 3) {
        printf("YES\n");
        if (n == 2) {
            printf("1\n%d\n1\n%d\n", m[0].key, m[1].key);
        } else {
            printf("1\n%d\n0\n\n", m[0].key);
        }
        return 0; 
    }

    int a[200001], b[200001];
    int a_count = 0, b_count = 0;

    for (int i = 0; i < m_count; i++) {
        if (m[i].value > 2) {
            printf("NO\n");
            return 0;
        } else if (m[i].value == 2) {
            b[b_count++] = m[i].key;
        }
        a[a_count++] = m[i].key;
    }

    printf("YES\n");
    printf("%d\n", a_count);
    for (int i = 0; i < a_count; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("%d\n", b_count);
    for (int i = b_count - 1; i >= 0; i--) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // POST: The output successfully composed of strictly increasing and decreasing sequences
    assert(a_count + b_count == n); // POST: Total elements equal original
    return 0;
}