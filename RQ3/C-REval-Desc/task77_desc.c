void bf(const char* planet1, const char* planet2) {
    const char* planet_names[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
    int planet1_index = -1, planet2_index = -1;
    int valid = 0;

    for (int i = 0; i < 8; i++) {
        if (strcmp(planet1, planet_names[i]) == 0) {
            planet1_index = i;
        }
        if (strcmp(planet2, planet_names[i]) == 0) {
            planet2_index = i;
        }
    }

    if (planet1_index != -1 && planet2_index != -1 && planet1_index != planet2_index) {
        valid = 1;
    }

    const char** _result = NULL;
    int count = 0;

    if (valid) {
        if (planet1_index < planet2_index) {
            count = planet2_index - planet1_index - 1;
            _result = malloc(count * sizeof(char*));
            for (int i = 0; i < count; i++) {
                _result[i] = planet_names[planet1_index + 1 + i];
            }
        } else {
            count = planet1_index - planet2_index - 1;
            _result = malloc(count * sizeof(char*));
            for (int i = 0; i < count; i++) {
                _result[i] = planet_names[planet2_index + 1 + i];
            }
        }
    }

    // Assume func is defined elsewhere and checks _result
    assert(func(_result));  

    // Free allocated memory if necessary
    if (_result) {
        free(_result);
    }
}