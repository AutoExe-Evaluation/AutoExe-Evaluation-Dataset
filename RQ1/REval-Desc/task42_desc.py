def closest_integer(value):
    if value.count('.') == 1:
        # remove trailing zeros
        while (value[-1] == '0'):
            value = value[:-1]

    num = float(value)
    if value[-2:] == '.5':
        if num > 0:
            res = ceil(num)
        else:
            res = floor(num)
    elif len(value) > 0:
        res = int(round(num))
    else:
        res = 0

    _result = res


    assert func(_result)  # POST: func is equivalent to: Create a function that takes a value (string) representing a number and returns the closest integer to it. If the number is equidistant Examples >>> closest_integer("10") 10 >>> closest_integer("15.3") 15 Note: Rounding away farthest return 15 and closest_integer("-14.5") should return -15.