#include <stdio.h>

int func(int value);

int sum_squares(int lst[], int length) {
    int result[length];
    int result_length = 0;

    for (int i = 0; i < length; i++) {
        if (i % 3 == 0) {
            result[result_length++] = lst[i] * lst[i];
        } else if (i % 4 == 0 && i % 3 != 0) {
            result[result_length++] = lst[i] * lst[i] * lst[i];
        } else {
            result[result_length++] = lst[i];
        }
    }

    int _result = 0;
    for (int j = 0; j < result_length; j++) {
        _result += result[j];
    }

    assert(func(_result));

    return _result;
}