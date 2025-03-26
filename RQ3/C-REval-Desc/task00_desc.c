#include <stdbool.h>
#include <math.h>

bool has_close_elements(double numbers[], int length, double threshold) {
    bool _result = false;
    for (int idx = 0; idx < length; idx++) {
        for (int idx2 = 0; idx2 < length; idx2++) {
            if (idx != idx2) {
                double distance = fabs(numbers[idx] - numbers[idx2]);
                if (distance < threshold) {
                    _result = true;
                }
            }
        }
    }
    return _result;
}