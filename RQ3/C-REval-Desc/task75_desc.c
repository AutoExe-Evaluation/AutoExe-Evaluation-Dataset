#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int func(int result);

int specialFilter(int nums[], int size) {
    int count = 0;
    int odd_digits[] = {1, 3, 5, 7, 9};

    for (int i = 0; i < size; i++) {
        int num = nums[i];
        if (num > 10) {
            char number_as_string[12];
            sprintf(number_as_string, "%d", num);
            if (strchr("13579", number_as_string[0]) && strchr("13579", number_as_string[strlen(number_as_string) - 1])) {
                count++;
            }
        }
    }

    int _result = count;

    assert(func(_result));

    return _result;
}