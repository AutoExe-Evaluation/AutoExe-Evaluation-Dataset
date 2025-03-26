#include <stdio.h>
#include <assert.h>

#define ll long long

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    
    // PRE: x and y are natural numbers representing the die rolls of Yakko and Wakko
    assert(x >= 1 && x <= 6); // ensuring the first die roll is valid
    assert(y >= 1 && y <= 6); // ensuring the second die roll is valid
    
    int mx = (x > y) ? x : y;
    
    if (mx == 1)
        printf("1/1\n"); // POST: Dot wins with any roll
    else if (mx == 2)
        printf("5/6\n"); // POST: Dot can win with rolls 2, 3, 4, 5, or 6
    else if (mx == 3)
        printf("2/3\n"); // POST: Dot can win with rolls 3, 4, 5, or 6
    else if (mx == 4)
        printf("1/2\n"); // POST: Dot can win with rolls 4, 5, or 6
    else if (mx == 5)
        printf("1/3\n"); // POST: Dot can win with rolls 5 or 6
    else
        printf("1/6\n"); // POST: Dot can win only with a roll of 6

    return 0;
}