#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 51

int main() {
    int TC;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 1000); // PRE: Number of test cases should be between 1 and 1000

    while (TC--) {
        char s[MAX_LENGTH];
        int m[26] = {0};

        scanf("%s", s);
        assert(strlen(s) >= 2 && strlen(s) <= 50); // PRE: Length of string should be between 2 and 50
        assert(strcmp(s, strrev(s)) == 0); // PRE: String should be a palindrome

        for (int i = 0; s[i] != '\0'; i++) {
            m[s[i] - 'a']++;
        }

        int unique_count = 0;
        int less_than_two_count = 0;

        for (int i = 0; i < 26; i++) {
            if (m[i] > 0) {
                unique_count++;
                if (m[i] < 2) {
                    less_than_two_count++;
                }
            }
        }

        if (unique_count > 2) {
            printf("YES\n");
        } else if (unique_count < 2) {
            printf("NO\n");
        } else {
            if (less_than_two_count > 0) {
                printf("NO\n");
            } else {
                printf("YES\n");
            }
        }

        assert((unique_count > 2) || (unique_count == 2 && less_than_two_count == 0)); // POST: Should be able to rearrange to another palindrome if unique_count > 2 or exactly 2 with all > 1
    }

    return 0;
}