def sum_squares(lst: list[float]):
    """
    pre: len(lst) > 0 and all(x > 1 for x in lst)
    post: abs(sum(_)) >= abs(sum(lst))
    """
    result =[]
    for i in range(len(lst)):
        if i %3 == 0:
            result.append(lst[i]**2)
        elif i % 4 == 0 and i%3 != 0:
            result.append(lst[i]**3)
        else:
            result.append(lst[i])
    return result
