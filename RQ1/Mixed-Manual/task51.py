def exchange(lst):
    odd = 0
    even = 0
    for i in lst:
        if i%2 == 1:
            odd += 1
    for i in lst:
        if i%2 == 0:
            even += 1
    assert even + odd == len(lst)  # POST
