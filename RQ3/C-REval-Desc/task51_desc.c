void exchange(int lst1[], int size1, int lst2[], int size2) {
    int odd = 0;
    int even = 0;
    for (int i = 0; i < size1; i++) {
        if (lst1[i] % 2 == 1) {
            odd++;
        }
    }
    for (int i = 0; i < size2; i++) {
        if (lst2[i] % 2 == 0) {
            even++;
        }
    }
    const char* _result;
    if (even >= odd) {
        _result = "YES";
    } else {
        _result = "NO";
    }
    
    assert(func(_result));
}