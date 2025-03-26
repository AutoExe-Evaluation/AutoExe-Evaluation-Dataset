#include <math.h>
#include <assert.h>

int func(int _result);

int sum_squares(double lst[], int size) {
    int squared = 0;
    for (int i = 0; i < size; i++) {
        squared += ceil(lst[i]) * ceil(lst[i]);
    }
    int _result = squared;

    assert(func(_result));
    return _result;
}