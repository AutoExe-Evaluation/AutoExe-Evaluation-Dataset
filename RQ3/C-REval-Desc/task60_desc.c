#include <stdio.h>

int func(const char* result);

const char* intersection(int interval1[2], int interval2[2]) {
    int l = interval1[0] > interval2[0] ? interval1[0] : interval2[0];
    int r = interval1[1] < interval2[1] ? interval1[1] : interval2[1];
    int length = r - l;
    int isPrime = 1;

    if (length <= 1) {
        isPrime = 0;
    } else {
        for (int i = 2; i < length; i++) {
            if (length % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }

    const char* _result = "NO";
    if (length > 0 && isPrime) {
        _result = "YES";
    }

    return func(_result);
}