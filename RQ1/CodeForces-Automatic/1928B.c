#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;
typedef struct {
    int *data;
    int size;
    int capacity;
} Set;

void initSet(Set *set) {
    set->size = 0;
    set->capacity = 10;
    set->data = (int *)malloc(set->capacity * sizeof(int));
}

void insertSet(Set *set, int val) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == val) {
            return;
        }
    }
    if (set->size == set->capacity) {
        set->capacity *= 2;
        set->data = (int *)realloc(set->data, set->capacity * sizeof(int));
    }
    set->data[set->size++] = val;
}

int sizeSet(Set *set) {
    return set->size;
}

int minSet(Set *set) {
    int min = set->data[0];
    for (int i = 1; i < set->size; i++) {
        if (set->data[i] < min) {
            min = set->data[i];
        }
    }
    return min;
}

void eraseMin(Set *set) {
    int minValue = minSet(set);
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == minValue) {
            set->data[i] = set->data[set->size - 1];
            set->size--;
            break;
        }
    }
}

void freeSet(Set *set) {
    free(set->data);
}

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 20000); // PRE: 1 ≤ t ≤ 2 * 10^4
    
    while (TC--) {
        int n;
        scanf("%d", &n);
        assert(n >= 1 && n <= 200000); // PRE: 1 ≤ n ≤ 2 * 10^5
        
        Set s1, s2;
        initSet(&s1);
        initSet(&s2);
        
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            assert(x >= 1 && x <= 1000000000); // PRE: 1 ≤ a_i ≤ 10^9
            insertSet(&s1, x);
            insertSet(&s2, x + n);
        }
        
        int ans = 0, ct = 0;
        
        for (int i = 0; i < s1.size; i++) {
            ct++;
            while (sizeSet(&s2) && minSet(&s2) <= s1.data[i]) {
                eraseMin(&s2);
                ct--;
            }
            if (ct > ans) {
                ans = ct;
            }
        }
        
        printf("%d\n", ans);
        
        freeSet(&s1);
        freeSet(&s2);
        
        assert(ans <= n); // POST: The maximum count cannot exceed the size of the array
    }
    
    return 0;
}