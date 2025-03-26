#include <stdbool.h>

bool is_sorted(int lst[], int length) {
    int count_digit[100] = {0}; // Assuming numbers are in range 0-99
    bool _result;

    for (int i = 0; i < length; i++) {
        count_digit[lst[i]]++;
    }
    
    for (int i = 0; i < 100; i++) {
        if (count_digit[i] > 2) {
            _result = false;
            goto check_sorted;
        }
    }

    for (int i = 1; i < length; i++) {
        if (lst[i - 1] > lst[i]) {
            _result = false;
            goto final;
        }
    }
    
    _result = true;

final:
    // This is where the assert func(_result) would go
    return _result;

check_sorted:
    _result = false;
    goto final;
}