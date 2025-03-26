def largest_prime_factor(n: int):
    largest = 1
    for j in range(2, n + 1):
        is_prime = True
        if j < 2:
            is_prime = False
        for i in range(2, j - 1):
            if j % i == 0:
                is_prime = False
        if n % j == 0 and is_prime:
            largest = max(largest, j)
    _result = largest

    assert func(_result)  # POST: func is equivalent to: Return the largest prime factor of n. Assume n > 1 and is not a prime. >>> largest_prime_factor(13195) 29 >>> largest_prime_factor(2048) 2
