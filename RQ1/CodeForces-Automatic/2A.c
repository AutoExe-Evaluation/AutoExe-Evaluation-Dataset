#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_PLAYERS 1000
#define MAX_NAME_LENGTH 33

typedef struct {
    char name[MAX_NAME_LENGTH];
    long long score;
} Player;

int main() {
    long long n;
    scanf("%lld", &n);
    assert(n >= 1 && n <= 1000); // PRE: Number of rounds must be between 1 and 1000

    Player players[MAX_PLAYERS];
    long long scores[MAX_PLAYERS] = {0};
    long long round_scores[MAX_PLAYERS] = {0};
    long long max_score = 0;
    int player_count = 0;

    for (long long i = 0; i < n; ++i) {
        char name[MAX_NAME_LENGTH];
        long long score;
        scanf("%s %lld", name, &score);
        
        assert(strlen(name) < MAX_NAME_LENGTH); // PRE: Player name must be within the allowed length

        int j;
        for (j = 0; j < player_count; ++j) {
            if (strcmp(players[j].name, name) == 0) {
                scores[j] += score;
                round_scores[j] += score;
                break;
            }
        }
        if (j == player_count) {
            strcpy(players[player_count].name, name);
            scores[player_count] = score;
            round_scores[player_count] = score;
            player_count++;
        }
    }
    
    for (int i = 0; i < player_count; ++i) {
        if (scores[i] > max_score) {
            max_score = scores[i];
        }
    }

    assert(max_score > 0); // POST: Maximum score must be positive

    for (int i = 0; i < player_count; ++i) {
        if (round_scores[i] >= max_score && scores[i] == max_score) {
            printf("%s\n", players[i].name);
            break;
        }
    }

    return 0;
}