int digits(int n) {
    int product = 1;
    int odd_count = 0;
    int int_digit;
    while (n > 0) {
        int_digit = n % 10;
        n /= 10;
        if (int_digit % 2 == 1) {
            product *= int_digit;
            odd_count++;
        }
    }
    int _result;
    if (odd_count == 0) {
        _result = 0;
    } else {
        _result = product;
    }

    return func(_result);
}