#include <stdio.h>
#include <assert.h>

int main() {
    int n, a = 0, d = 0;
    
    // PRE: n must be in the range [1, 100000]
    scanf("%d", &n);
    assert(n >= 1 && n <= 100000); // PRE: n is within valid range

    char s[n + 1];
    scanf("%s", s);
    
    // Count wins
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') a++;
        else d++;
    }
    
    // Determine winner
    if (a == d) {
        printf("Friendship\n");
        // POST: a == d implies a must equal d which leads to Friendship
        assert(a == d); // POST: Anton and Danik won the same number of games
    }
    else if (a > d) {
        printf("Anton\n");
        // POST: a > d implies Anton has more wins
        assert(a > d); // POST: Anton won more games
    }
    else {
        printf("Danik\n");
        // POST: d > a implies Danik has more wins
        assert(d > a); // POST: Danik won more games
    }
    
    return 0;
}