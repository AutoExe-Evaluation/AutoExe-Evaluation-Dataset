def all_prefixes(string: str) -> List[str]:
    result = []

    for i in range(len(string)):
        result.append(string[:i+1])
    _result = result

    assert func(_result)  # POST: func is equivalent to: Return list of all prefixes >>> all_prefixes('abc') ['a', 'ab', 'abc']