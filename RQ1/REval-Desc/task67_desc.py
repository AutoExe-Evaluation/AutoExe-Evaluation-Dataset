def compare_one(a, b):
    temp_a = a
    temp_b = b
    if isinstance(temp_a, str): temp_a = temp_a.replace(',','.')
    if isinstance(temp_b, str): temp_b = temp_b.replace(',','.')
    if float(temp_a) == float(temp_b): _result = None
    if float(temp_a) > float(temp_b):
        _result = a
    else:
        _result = b

    assert func(_result)  # POST: func is equivalent to: Create a function that takes integers, floats, or strings representing real numbers, and returns the larger variable in its given variable type. Return None if the values are equal. Note: If a real number is represented as a string, the floating point might be . or , compare_one(1, 2.5) ➞ 2.5 compare_one(1, "2,3") ➞ "2,3" compare_one("5,1", "6") ➞ "6" compare_one("1", 1) ➞ None
