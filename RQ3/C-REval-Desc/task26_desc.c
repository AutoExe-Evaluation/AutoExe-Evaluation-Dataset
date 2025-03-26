char* circular_shift(int x, int shift) {
    char s[20];
    sprintf(s, "%d", x);
    int len = strlen(s);
    char* _result = (char*)malloc(len + 1);

    if (shift > len) {
        for (int i = 0; i < len; i++) {
            _result[i] = s[len - 1 - i];
        }
        _result[len] = '\0';
    } else {
        strncpy(_result, s + (len - shift), shift);
        strncpy(_result + shift, s, len - shift);
        _result[len] = '\0';
    }

    assert(func(_result));
    return _result;
}