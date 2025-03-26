void words_string(char *s) {
    char *result[100]; // assuming max 100 words
    int result_index = 0;

    if (s[0] == '\0') {
        return;
    }

    char s_list[1000]; // assuming max length of input string
    int s_index = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ',') {
            s_list[s_index++] = ' ';
        } else {
            s_list[s_index++] = s[i];
        }
    }
    s_list[s_index] = '\0';

    char *token = strtok(s_list, " ");
    while (token != NULL) {
        result[result_index++] = token;
        token = strtok(NULL, " ");
    }

    // The assertion for func is handled externally
    assert(func(result)); 
}