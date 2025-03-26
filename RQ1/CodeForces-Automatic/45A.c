#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char months[12][10] = {
        "January", "February", "March", "April", 
        "May", "June", "July", "August", 
        "September", "October", "November", "December"
    };
    char s[10];
    int n;

    scanf("%s %d", s, &n);
    assert(n >= 0 && n <= 100); // PRE: k must be between 0 and 100 inclusive.
    
    int index;

    for (index = 0; index < 12; index++) {
        if (strcmp(months[index], s) == 0) {
            break;
        }
    }
    
    assert(index < 12); // PRE: month must be one of the valid months.

    index = (n + index) % 12;
    printf("%s\n", months[index]);

    assert(strcmp(months[index], "") != 0); // POST: Output month must be a valid month name.
    return 0;
}