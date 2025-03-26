int is_simple_power(int x, int n) {
    int _result;
    if (n == 1) {
        _result = (x == 1);
    } else {
        int power = 1;
        while (power < x) {
            power = power * n;
        }
        _result = (power == x);
    }

    assert(func(_result));
    return _result;
}