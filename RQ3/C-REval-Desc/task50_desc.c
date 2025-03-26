void move_one_ball(int arr[], int len) {
    int _result = 1; // True
    if (len == 0) {
        _result = 1; // True
    }

    int sorted_array[len];
    for (int i = 0; i < len; i++) {
        sorted_array[i] = arr[i];
    }
    // Sorting the array
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (sorted_array[j] > sorted_array[j + 1]) {
                int temp = sorted_array[j];
                sorted_array[j] = sorted_array[j + 1];
                sorted_array[j + 1] = temp;
            }
        }
    }

    int min_value = arr[0];
    int min_index = 0;
    for (int i = 1; i < len; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
            min_index = i;
        }
    }

    int my_arr[len];
    for (int i = 0; i < len; i++) {
        if (i < len - min_index) {
            my_arr[i] = arr[i + min_index];
        } else {
            my_arr[i] = arr[i - (len - min_index)];
        }
    }

    for (int i = 0; i < len; i++) {
        if (my_arr[i] != sorted_array[i]) {
            _result = 0; // False
        }
    }
    _result = 1; // True

    assert(func(_result));
}