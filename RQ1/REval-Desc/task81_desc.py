def even_odd_count(num):
    even_count = 0
    odd_count = 0
    for i in str(abs(num)):
        if int(i)%2==0:
            even_count +=1
        else:
            odd_count +=1
    _result = (even_count, odd_count)

    assert func(_result)  # POST: func is equivalent to: Given an integer. return a tuple that has the number of even and odd digits respectively. Example: even_odd_count(-12) ==> (1, 1) even_odd_count(123) ==> (1, 2)