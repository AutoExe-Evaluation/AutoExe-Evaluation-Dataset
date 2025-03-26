def intersperse(numbers: list[int], delimeter: int):
    """
    pre: len(numbers) > 0
    post: _.count(delimeter) * 2 + 1 >= len(_)
    """
    result = []

    for n in numbers[:-1]:
        result.append(n)
        result.append(delimeter)

    result.append(numbers[-1])

    return result
