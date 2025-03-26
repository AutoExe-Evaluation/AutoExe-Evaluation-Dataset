#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    char a[101], b[101], c[101];
    scanf("%s", a);
    scanf("%s", b);
    scanf("%s", c);
    
    assert(strlen(a) + strlen(b) == strlen(c)); // PRE: Length of guest's name + host's name should equal pile length
    
    int letters[26] = {0};
    
    for(int i = 0; a[i] != '\0'; ++i) {
        letters[a[i] - 'A']++;
    }
    for(int i = 0; b[i] != '\0'; ++i) {
        letters[b[i] - 'A']++;
    }
    
    for(int i = 0; c[i] != '\0'; ++i) {
        letters[c[i] - 'A']--;
    }
    
    int matching = 1;
    for(int i = 0; i < 26; ++i) {
        if(letters[i] != 0) {
            matching = 0;
            break;
        }
    }
    
    assert(matching || !matching); // POST: Either matching is true, or it is false, indicating the names cannot be formed
    
    if(matching)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}