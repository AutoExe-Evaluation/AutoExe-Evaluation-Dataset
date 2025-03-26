#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_NAMES 100
#define MAX_LENGTH 101

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 100); // PRE: 1 ≤ n ≤ 100

    char names[MAX_NAMES][MAX_LENGTH];
    bool found[MAX_NAMES] = {false};

    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
        assert(strlen(names[i]) >= 1 && strlen(names[i]) < MAX_LENGTH); // PRE: length of each string is between 1 and 100
        
        bool alreadyExists = false;
        
        for (int j = 0; j < i; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                alreadyExists = true;
                break;
            }
        }
        
        if (alreadyExists) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    // POST: All outputs correspond to whether a name was previously seen or not
    // This will be implicitly true if the program finishes without error
    return 0;
}