#include <stdio.h>
#include <limits.h>
#include <assert.h>

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    assert(a >= 1 && a <= 100000000 && b >= 1 && b <= 100000000 && c >= 1 && c <= 100000000); // PRE: 1 ≤ d1, d2, d3 ≤ 10^8

    int min_distance = INT_MAX;

    min_distance = a + b + c;        // Path 1: H -> A -> B -> H
    min_distance = (min_distance < 2 * a + 2 * b) ? min_distance : (2 * a + 2 * b); // Path 2: H -> A -> H -> B -> H
    min_distance = (min_distance < 2 * a + 2 * c) ? min_distance : (2 * a + 2 * c); // Path 3: H -> A -> H -> C -> H
    min_distance = (min_distance < 2 * b + 2 * c) ? min_distance : (2 * b + 2 * c); // Path 4: H -> B -> H -> C -> H

    printf("%d\n", min_distance);
    assert(min_distance >= 0); // POST: min_distance is non-negative
    return 0;
}