def is_simple_power(x, n):
    if (n == 1): 
        _result = (x == 1) 
    else:
        power = 1
        while (power < x): 
            power = power * n 
        _result = (power == x) 

    assert func(_result)  # POST: func is equivalent to: Your task is to write a function that returns true if a number x is a simple power of n and false in other cases. x is a simple power of n if n**int=x For example: is_simple_power(1, 4) => true is_simple_power(2, 2) => true is_simple_power(8, 2) => true is_simple_power(3, 2) => false is_simple_power(3, 1) => false is_simple_power(5, 3) => false
