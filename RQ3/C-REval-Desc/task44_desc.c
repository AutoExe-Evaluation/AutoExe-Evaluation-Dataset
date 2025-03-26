int rounded_avg(int n, int m) {
    int _result;
    if (m < n) {
        _result = -1;
    } else {
        int summation = 0;
        for (int i = n; i <= m; i++) {
            summation += i;
        }
        _result = (int)round((double)summation / (m - n + 1));
        char bin_result[50];
        sprintf(bin_result, "0b%s", itoa(_result, NULL, 2));
        _result = bin_result;  // Note: This is conceptual, proper conversion needed
    }

    assert(func(_result));
    return _result;
}