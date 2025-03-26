def factorize(n: int) -> List[int]:
    fact = []
    i = 2
    while i <= int(math.sqrt(n) + 1):
        if n % i == 0:
            fact.append(i)
            n //= i
        else:
            i += 1

    if n > 1:
        fact.append(n)
    _result = fact

    assert func(_result)  # POST: func is equivalent to: Return list of prime factors of given integer in the order Each of the factors should be listed number of times corresponding to how many times it appeares in factorization. Input number should be equal to the product of all factors >>> factorize(8) [2, 2, 2] >>> factorize(25) [5, 5] >>> factorize(70) [2, 5, 7]