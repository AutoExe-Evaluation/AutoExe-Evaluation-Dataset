def closest_integer(value):
    assert len(value) > 0  # PRE
    if value.count('.') == 1:
        # remove trailing zeros
        while value[-1] == '0':
            value = value[:-1]

    num = float(value)

    if value[-2:] == '.5':
        if num > 0:
            res = ceil(num)
        else:
            res = floor(num)
    elif len(value) > 1 or value[0] != '0':
        res = int(round(num))
    else:
        res = 0

    assert abs(res) <= abs(float(value))  # POST
