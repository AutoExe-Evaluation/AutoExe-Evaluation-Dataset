#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int func(int value); // Assume func is defined elsewhere

int closest_integer(const char *value) {
    char *end;
    double num;
    int res;

    if (strchr(value, '.') != NULL) {
        char *temp = strdup(value);
        while (temp[strlen(temp) - 1] == '0') {
            temp[strlen(temp) - 1] = '\0';
        }
        if (temp[strlen(temp) - 1] == '.') {
            temp[strlen(temp) - 1] = '\0';
        }
        num = strtod(temp, &end);
        free(temp);
    } else {
        num = strtod(value, &end);
    }

    if (strcmp(end - 2, ".5") == 0) {
        if (num > 0) {
            res = ceil(num);
        } else {
            res = floor(num);
        }
    } else if (strlen(value) > 0) {
        res = (int)round(num);
    } else {
        res = 0;
    }

    int _result = res;

    // Assert func is equivalent
    if (!func(_result)) {
        // Handle assertion failure
        exit(1);
    }

    return _result;
}