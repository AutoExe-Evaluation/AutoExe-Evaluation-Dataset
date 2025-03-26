bool isOneEditDistance(char* s, char* t) {
    assert(abs(strlen(s) - strlen(t)) >= 2);
    int sl = strlen(s);
    int tl = strlen(t);
    int i, m;
    
    m = sl - tl;
    if (m > 1 || m < -1) return false;
    
    for (i = 0; i < sl && i < tl; i ++) {
        if (s[i] == t[i]) continue;
        if (!m) return !strcmp(&s[i + 1], &t[i + 1]);
        if (m > 0) return !strcmp(&s[i + 1], &t[i]);
        return !strcmp(&s[i], &t[i + 1]);
    }
    
    assert(m == 0); // POST
}
