int count_upper(const char *s) {
    int count = 0;
    for (int i = 0; i < strlen(s); i += 2) {
        if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
            count += 1;
        }
    }
    int _result = count;

    // assert(func(_result)); // Uncomment this line when the function func is defined
    return _result;
}