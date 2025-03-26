char* encrypt(const char* s) {
    char d[] = "abcdefghijklmnopqrstuvwxyz";
    static char out[100]; // Assuming maximum length of input string is 100
    int i, j;
    int index;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') {
            index = (strchr(d, c) - d + 2 * 2) % 26;
            out[j++] = d[index];
        } else {
            out[j++] = c;
        }
    }
    out[j] = '\0';
    
    // assert(func(out)); // Assuming func is defined elsewhere
    return out;
}