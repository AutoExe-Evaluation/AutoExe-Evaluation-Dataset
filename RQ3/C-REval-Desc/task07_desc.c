char* make_palindrome(const char* string) {
    if (string[0] == '\0') {
        return "";
    }

    int beginning_of_suffix = 0;
    int length = strlen(string);
    char* _result;

    while (strncmp(string + beginning_of_suffix, strrev(string + beginning_of_suffix), length - beginning_of_suffix) != 0) {
        beginning_of_suffix++;
    }

    _result = (char*)malloc((length + beginning_of_suffix + 1) * sizeof(char));
    strcpy(_result, string);
    strncat(_result, string, beginning_of_suffix);
    strrev(_result + length); 

    assert(func(_result));
    return _result;
}