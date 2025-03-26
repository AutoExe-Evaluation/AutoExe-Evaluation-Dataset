int can_arrange(int arr[], int length) {
    int ind = -1;
    int i = 1;
    while (i < length) {
        if (arr[i] < arr[i - 1]) {
            ind = i;
        }
        i++;
    }
    int _result = ind;

    assert(func(_result)); // POST: func is defined elsewhere
    return _result;
}