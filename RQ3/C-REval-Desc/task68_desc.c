int special_factorial(int n) {
    int fact_i = 1;
    int special_fact = 1;
    for (int i = 1; i <= n; i++) {
        fact_i *= i;
        special_fact *= fact_i;
    }
    int _result = special_fact;

    assert(func(_result)); 
    return _result;
}