#include <stdio.h>
#include <assert.h>

#define int long long

int main() {
    int TC = 1;
    scanf("%lld", &TC);
    assert(TC >= 1 && TC <= 108); // PRE: 1 ≤ t ≤ 10^8
    while (TC--) {
        int freq[3] = {0, 0, 0};
        for(int i = 0; i < 3; ++i) {
            char s[4];
            scanf("%s", s);
            assert(s[3] == '\0'); // Assure null-terminated string
            for(int j = 0; j < 3; ++j) {
                if(s[j] == '?')
                    continue;
                else {
                    assert(s[j] >= 'A' && s[j] <= 'C'); // PRE: input characters are A, B, C or ?
                    freq[s[j] - 'A']++;
                }
            }
        }
        char missing = 0;
        for(int i = 0; i < 3; ++i) {
            if(freq[i] < 3) {
                missing = i + 'A';
                break;
            }
        }
        printf("%c\n", missing);
        assert(missing >= 'A' && missing <= 'C'); // POST: Replaced letter is one of A, B, C
    }
    return 0;
}