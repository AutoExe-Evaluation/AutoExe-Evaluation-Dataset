int how_many_times(char *string, char *substring) {
    int times = 0;
    int len_string = strlen(string);
    int len_substring = strlen(substring);

    for (int i = 0; i <= len_string - len_substring; i++) {
        if (strncmp(&string[i], substring, len_substring) == 0) {
            times++;
        }
    }

    int _result = times;

    assert(func(_result));
    return _result;
}