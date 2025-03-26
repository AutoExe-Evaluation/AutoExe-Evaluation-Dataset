def sum_product(numbers: List[int]) -> Tuple[int, int]:
    sum_value = 0
    prod_value = 1

    for n in numbers:
        sum_value += n
        prod_value *= n
    _result = sum_value, prod_value

    assert func(_result)  # POST: func is equivalent to: For a given list of integers, return a tuple consisting of a sum and a product of all the integers in a list. Empty sum should be equal to 0 and empty product should be equal to 1. >>> sum_product([]) (0, 1) >>> sum_product([1, 2, 3, 4]) (10, 24)