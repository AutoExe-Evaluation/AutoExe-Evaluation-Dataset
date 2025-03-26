def order_by_points(nums):
    def digits_sum(n):
        neg = 1
        if n < 0:
            n = -1 * n
            neg = -1 
        n = [int(i) for i in str(n)]
        n[0] = n[0] * neg
        return sum(n)
    _result = sorted(nums, key=digits_sum)

    assert func(_result)  # POST: func is equivalent to: Write a function which sorts the given list of integers in ascending order according to the sum of their digits. Note: if there are several items with similar sum of their digits, order them based on their index in original list. For example: >>> order_by_points([1, 11, -1, -11, -12]) == [-1, -11, 1, -12, 11] >>> order_by_points([]) == []
