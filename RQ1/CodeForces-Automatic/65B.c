#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int main() {
    int n;
    scanf("%d", &n);
    assert(n >= 1 && n <= 1000); // PRE: 1 ≤ n ≤ 1000
    char dates[1000][5];
    
    for(int i = 0; i < n; i++) {
        scanf("%s", dates[i]);
        assert(strlen(dates[i]) == 4 && dates[i][0] != '0'); // PRE: each date is a 4-digit number, first digit not '0'
    }
    
    char prev[5] = "1000";
    
    for(int i = 0; i < n; i++) {
        char best[5] = "9999";
        int found = 0;

        for(int digit = 0; digit < 4; digit++) {
            for(char c = '0'; c <= '9'; c++) {
                if(digit == 0 && c == '0') continue;
                
                char temp[5];
                strcpy(temp, dates[i]);
                temp[digit] = c;
                
                if(strcmp(temp, "1000") >= 0 && strcmp(temp, "2011") <= 0 && strcmp(temp, prev) >= 0) {
                    found = 1;
                    if(strcmp(temp, best) < 0) {
                        strcpy(best, temp);
                    }
                }
            }
        }
        
        if(!found) {
            printf("No solution\n");
            return 0;
        }
        
        strcpy(prev, best);
        strcpy(dates[i], best);
    }

    for(int i = 0; i < n; i++) {
        printf("%s\n", dates[i]);
        assert(strcmp(dates[i], "1000") >= 0 && strcmp(dates[i], "2011") <= 0); // POST: each date is between 1000 and 2011
        if (i > 0) {
            assert(strcmp(dates[i], dates[i-1]) >= 0); // POST: dates must be in non-decreasing order
        }
    }

    return 0;
}