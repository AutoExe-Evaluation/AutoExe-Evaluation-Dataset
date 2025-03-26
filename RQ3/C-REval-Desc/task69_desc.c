char* fix_spaces(const char* text) {
    int i = 0, start = 0, end = 0;
    char* new_text = malloc(1024); // Assume allocated size is enough
    new_text[0] = '\0';

    while (text[i] != '\0') {
        if (text[i] == ' ') {
            end++;
        } else {
            if (end - start > 2) {
                strcat(new_text, "-");
                strncat(new_text, &text[i], 1);
            } else if (end - start > 0) {
                for (int j = 0; j < end - start; j++) {
                    strncat(new_text, "_", 1);
                }
                strncat(new_text, &text[i], 1);
            } else {
                strncat(new_text, &text[i], 1);
            }
            start = i + 1;
            end = i + 1;
        }
        i++;
    }
    if (end - start > 2) {
        strcat(new_text, "-");
    } else if (end - start > 0) {
        strcat(new_text, "_");
    }
    char* _result = new_text;

    assert(func(_result));
    return _result;
}