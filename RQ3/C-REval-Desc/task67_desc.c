void compare_one(void* a, void* b) {
    void* temp_a = a;
    void* temp_b = b;
    
    if (is_string(temp_a)) temp_a = replace(temp_a, ',', '.');
    if (is_string(temp_b)) temp_b = replace(temp_b, ',', '.');

    double float_a = atof(temp_a);
    double float_b = atof(temp_b);
    
    void* _result;
    if (float_a == float_b) {
        _result = NULL;
    } else if (float_a > float_b) {
        _result = a;
    } else {
        _result = b;
    }

    assert(func(_result));
}