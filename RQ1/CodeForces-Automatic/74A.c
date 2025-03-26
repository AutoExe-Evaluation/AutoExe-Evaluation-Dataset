#include <stdio.h>
#include <string.h>
#include <assert.h>

struct Contestant {
    char handle[21];
    int successful_hacks;
    int unsuccessful_hacks;
    int points_A;
    int points_B;
    int points_C;
    int points_D;
    int points_E;
    int total_points;
};

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 50); // PRE: 1 ≤ n ≤ 50
    struct Contestant contestants[50];
    
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d %d %d %d %d", contestants[i].handle, 
              &contestants[i].successful_hacks, 
              &contestants[i].unsuccessful_hacks, 
              &contestants[i].points_A, 
              &contestants[i].points_B, 
              &contestants[i].points_C, 
              &contestants[i].points_D, 
              &contestants[i].points_E);
        
        contestants[i].total_points = contestants[i].successful_hacks * 100 - contestants[i].unsuccessful_hacks * 50 +
                                       contestants[i].points_A + contestants[i].points_B + contestants[i].points_C +
                                       contestants[i].points_D + contestants[i].points_E;
        
        assert(contestants[i].points_A == 0 || (contestants[i].points_A >= 150 && contestants[i].points_A <= 500)); // Check problem A points
        assert(contestants[i].points_B == 0 || (contestants[i].points_B >= 300 && contestants[i].points_B <= 1000)); // Check problem B points
        assert(contestants[i].points_C == 0 || (contestants[i].points_C >= 450 && contestants[i].points_C <= 1500)); // Check problem C points
        assert(contestants[i].points_D == 0 || (contestants[i].points_D >= 600 && contestants[i].points_D <= 2000)); // Check problem D points
        assert(contestants[i].points_E == 0 || (contestants[i].points_E >= 750 && contestants[i].points_E <= 2500)); // Check problem E points
    }

    int max_points = contestants[0].total_points;
    int leader_index = 0;

    for (int i = 1; i < n; i++) {
        if (contestants[i].total_points > max_points) {
            max_points = contestants[i].total_points;
            leader_index = i;
        }
    }

    assert(max_points >= 0); // POST: Leader's total points are non-negative
    printf("%s\n", contestants[leader_index].handle);
    return 0;
}