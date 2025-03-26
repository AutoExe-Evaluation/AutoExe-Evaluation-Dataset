def circular_shift(x, shift):
    s = str(x)
    if shift > len(s):
        _result = s[::-1]
    else:
        _result = s[len(s) - shift:] + s[:len(s) - shift]

    assert func(_result)  # POST: func is equivalent to: Circular shift the digits of the integer x, shift the digits right by shift and return the result as a string. If shift > number of digits, return digits reversed. >>> circular_shift(12, 1) "21" >>> circular_shift(12, 2) "12"