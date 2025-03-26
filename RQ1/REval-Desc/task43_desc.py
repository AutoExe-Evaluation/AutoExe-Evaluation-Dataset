def words_string(s):
    if not s:
        _result = []

    s_list = []

    for letter in s:
        if letter == ',':
            s_list.append(' ')
        else:
            s_list.append(letter)

    s_list = "".join(s_list)
    _result = s_list.split()

    assert func(_result)  # POST: func is equivalent to: You will be given a string of words separated by commas or spaces. Your task is to split the string into words and return an array of the words. For example: words_string("Hi, my name is John") == ["Hi", "my", "name", "is", "John"] words_string("One, two, three, four, five, six") == ["One", "two", "three", "four", "five", "six"]