def exchange(lst: list[int]):
    """
    pre: True
    post: _ == len(lst)
    """
    odd = 0
    even = 0
    for i in lst:
        if i%2 == 1:
            odd += 1
    for i in lst:
        if i%2 == 0:
            even += 1
    return even + odd
