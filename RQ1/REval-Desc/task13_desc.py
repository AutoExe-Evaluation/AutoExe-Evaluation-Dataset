def max_element(l: list):
    m = l[0]
    for e in l:
        if e > m:
            m = e
    _result = m

    assert func(_result)  # POST: func is equivalent to: Return maximum element in the list. >>> max_element([1, 2, 3]) 3 >>> max_element([5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10]) 123