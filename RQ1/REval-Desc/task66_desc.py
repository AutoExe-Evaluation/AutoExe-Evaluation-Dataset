def can_arrange(arr):
    ind=-1
    i=1
    while i<len(arr):
      if arr[i]<arr[i-1]:
        ind=i
      i+=1
    _result = ind

    assert func(_result)  # POST: func is equivalent to: Create a function which returns the largest index of an element which is not greater than or equal to the element immediately preceding it. If no such element exists then return -1. The given array will not contain duplicate values. Examples: can_arrange([1,2,4,3,5]) = 3 can_arrange([1,2,3]) = -1