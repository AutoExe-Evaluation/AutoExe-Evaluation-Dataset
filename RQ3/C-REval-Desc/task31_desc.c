#include <stdbool.h>

bool func(bool result);

bool will_it_fly(int q[], int length, int w) {
    bool _result = true;
    int sum = 0;

    for (int k = 0; k < length; k++) {
        sum += q[k];
    }
    
    if (sum > w) {
        _result = false;
    }

    int i = 0;
    int j = length - 1;
    while (i < j) {
        if (q[i] != q[j]) {
            _result = false;
        }
        i++;
        j--;
    }

    return func(_result);
}