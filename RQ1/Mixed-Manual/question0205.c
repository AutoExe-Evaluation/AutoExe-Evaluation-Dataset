bool isIsomorphic(char* s, char* t) {
    char a[128] = { 0 };
    char b[128] = { 0 };
    bool result = true;
    while (*s) {
        //printf("%c:%c\n", *s, *t);
        if (a[*s] == 0 && b[*t] == 0) {
            a[*s] = *t;
            b[*t] = *s;
        } else if (a[*s] == *t && b[*t] == *s) {
        } else {
            result = false;
            break;
        }
        s ++;
        t ++;
    }
    assert(!result || strlen(s) == strlen(t)); // POST
}
