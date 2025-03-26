#include <stdio.h>
#include <assert.h>

int main() {
    int q;
    scanf("%d", &q);
    assert(q >= 1 && q <= 1000); // PRE: number of test cases must be between 1 and 1000

    while (q--) {
        int n, t;
        scanf("%d %d", &n, &t);
        assert(n >= 1 && n <= 50); // PRE: number of videos must be between 1 and 50
        assert(t >= 1 && t <= 200); // PRE: lunch time must be between 1 and 200
        
        int a[50], b[50];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            assert(a[i] >= 1 && a[i] <= 100); // PRE: video duration must be between 1 and 100
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
            assert(b[i] >= 1 && b[i] <= 100); // PRE: entertainment value must be between 1 and 100
        }

        int ent = 0;
        int index = -1;
        
        for (int i = 0; i < n; i++) {
            if (a[i] <= t - i) {
                if (b[i] > ent) {
                    ent = b[i];
                    index = i + 1;
                }
            }
        }

        assert((index == -1) || (a[index - 1] <= t - (index - 1) && ent > 0)); // POST: if index is valid, it must be a video Mushroom can watch
        printf("%d\n", index);
    }
    return 0;
}