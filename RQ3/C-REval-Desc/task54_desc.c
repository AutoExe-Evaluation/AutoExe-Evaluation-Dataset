#include <stdio.h>

int func(int result);

int minSubArraySum(int* nums, int size) {
    int max_sum = 0;
    int s = 0;
    for (int i = 0; i < size; i++) {
        s += -nums[i];
        if (s < 0) {
            s = 0;
        }
        if (s > max_sum) {
            max_sum = s;
        }
    }
    if (max_sum == 0) {
        max_sum = -nums[0];
        for (int i = 1; i < size; i++) {
            if (-nums[i] > max_sum) {
                max_sum = -nums[i];
            }
        }
    }
    int min_sum = -max_sum;
    int _result = min_sum;

    if (!func(_result)) {
        return -1; // or some error handling
    }
    return _result;
}