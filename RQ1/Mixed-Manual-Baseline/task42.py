from math import ceil, floor

def closest_integer(value: str):
    """
    pre: len(value) > 0
    post: abs(_) <= abs(float(value))
    raises: ValueError
    """
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
    return res
