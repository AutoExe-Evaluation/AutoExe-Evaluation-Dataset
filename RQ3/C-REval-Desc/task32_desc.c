int smallest_change(int arr[], int len) {
    int ans = 0;
    for (int i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - i - 1]) {
            ans += 1;
        }
    }
    int _result = ans;

    assert(func(_result));
    
    return _result;
}