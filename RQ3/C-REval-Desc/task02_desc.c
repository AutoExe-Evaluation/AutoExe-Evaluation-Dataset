bool below_zero(int* operations, int size) {
    int balance = 0;
    bool _result = false;

    for (int i = 0; i < size; i++) {
        balance += operations[i];
        if (balance < 0) {
            _result = true;
        }
    }

    assert(func(_result)); 
    return _result;
}