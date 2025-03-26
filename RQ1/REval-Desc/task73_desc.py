def simplify(x, n):
    ab = x.split("/")
    cd = n.split("/")
    numerator = int(ab[0]) * int(cd[0])
    denom = int(ab[1]) * int(cd[1])
    _result = False
    if (numerator/denom == int(numerator/denom)):
        _result = True

    assert func(_result)  # POST: func is equivalent to: Your task is to implement a function that will simplify the expression x * n. The function returns True if x * n evaluates to a whole number and False otherwise. Both x and n, are string representation of a fraction, and have the following format, <numerator>/<denominator> where both numerator and denominator are positive whole numbers. You can assume that x, and n are valid fractions, and do not have zero as denominator. simplify("1/5", "5/1") = True simplify("1/6", "2/1") = False simplify("7/10", "10/2") = False
