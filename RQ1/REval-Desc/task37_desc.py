def prime_length(string):
    l = len(string)
    _result = True
    if l == 0 or l == 1:
        _result = False
    for i in range(2, l):
        if l % i == 0:
            _result = False

    assert func(_result)  # POST: func is equivalent to: Write a function that takes a string and returns True if the string length is a prime number or False otherwise Examples prime_length('Hello') == True prime_length('abcdcba') == True prime_length('kittens') == True prime_length('orange') == False
