def f(n):
    ret = []
    for i in range(1,n+1):
        if i%2 == 0:
            x = 1
            for j in range(1,i+1): x *= j
            ret += [x]
        else:
            x = 0
            for j in range(1,i+1): x += j
            ret += [x]
    _result = ret

    assert func(_result)  # POST: func is equivalent to: Implement the function f that takes n as a parameter, and returns a list of size n, such that the value of the element at index i is the factorial of i if i is even or the sum of numbers i starts the factorial of i is the multiplication of the numbers Example: f(5) == [1, 2, 6, 24, 15]