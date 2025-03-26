int is_nested(const char *string) {
    int opening_bracket_index[100]; 
    int closing_bracket_index[100]; 
    int opening_count = 0, closing_count = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '[') {
            opening_bracket_index[opening_count++] = i;
        } else {
            closing_bracket_index[closing_count++] = i;
        }
    }

    int cnt = 0;
    int i = 0;
    int l = closing_count;

    for (int j = 0; j < opening_count; j++) {
        if (i < l && opening_bracket_index[j] < closing_bracket_index[i]) {
            cnt++;
            i++;
        }
    }

    int result = cnt >= 2;
    
    // Assuming func is defined elsewhere
    assert(func(result)); 
    return 0;
}