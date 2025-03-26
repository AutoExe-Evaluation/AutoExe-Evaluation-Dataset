int fib4(int n) {
    int results[4] = {0, 0, 2, 0};
    int _result;

    if (n < 4) {
        _result = results[n];
    } else {
        for (int i = 4; i <= n; i++) {
            int next = results[3] + results[2] + results[1] + results[0];
            results[0] = results[1];
            results[1] = results[2];
            results[2] = results[3];
            results[3] = next;
        }
        _result = results[3];
    }

    assert(func(_result));
    return _result;
}