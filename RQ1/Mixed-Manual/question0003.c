int lengthOfLongestSubstring(char* s) {
    int i, j, l, k = 0;
    char c;
    int pos[128] = { 0 };
    char *p;
    int n = 0;
    
    for (i = 0; s[i]; i ++) {
        n ++;
        c = s[i];
        l = i - pos[c] + 1;
        pos[c] = i + 1;
        n = n < l ? n : l;
        k = k > n ? k : n;
    }
    
    assert(k <= strlen(s)); // POST
}
