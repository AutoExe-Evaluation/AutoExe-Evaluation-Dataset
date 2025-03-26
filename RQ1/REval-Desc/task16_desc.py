def prime_fib(n: int):
    f = [0, 1]
    while True:
        f.append(f[-1] + f[-2])
        is_prime = True
        if f[-1] < 2:
            is_prime = False
        for k in range(2, min(int(math.sqrt(f[-1])) + 1, f[-1] - 1)):
            if f[-1] % k == 0:
                is_prime = False
        if is_prime:
            n -= 1
        if n == 0:
            _result = f[-1]

    assert func(_result)  # POST: func is equivalent to: prime_fib returns n-th number that is a Fibonacci number and it's also prime. >>> prime_fib(1) 2 >>> prime_fib(2) 3 >>> prime_fib(3) 5 >>> prime_fib(4) 13 >>> prime_fib(5) 89
