def make_palindrome(string: str) -> str:
    if not string:
        _result = ''

    beginning_of_suffix = 0

    while string[beginning_of_suffix:] != string[beginning_of_suffix:][::-1]:
        beginning_of_suffix += 1

    _result = string + string[:beginning_of_suffix][::-1]

    assert func(_result)  # POST: func is equivalent to: Test if given string is a palindrome Find the shortest palindrome that begins with a supplied string. Algorithm idea is simple: - Find the longest postfix of supplied string that is a palindrome. - Append to the end of the string reverse of a string prefix that comes before the palindromic suffix. >>> make_palindrome('') '' >>> make_palindrome('cat') 'catac' >>> make_palindrome('cata') 'catac'
