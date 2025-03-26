def intersperse(numbers, delimeter):
    assert len(numbers) > 0  # PRE

    result = []

    for n in numbers[:-1]:
        result.append(n)
        result.append(delimeter)

    result.append(numbers[-1])

    assert result.count(delimeter) * 2 + 1 == len(result)  # POST
