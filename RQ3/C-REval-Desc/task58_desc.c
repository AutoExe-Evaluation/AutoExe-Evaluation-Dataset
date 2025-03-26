#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool func(bool result);

bool valid_date(char *date) {
    bool _result = true;
    date = strtok(date, "\n");
    if (date == NULL) return false;
    
    char *mdy = strtok(date, "-");
    int month = atoi(mdy);
    mdy = strtok(NULL, "-");
    int day = atoi(mdy);
    mdy = strtok(NULL, "-");
    int year = atoi(mdy);
    
    if (month < 1 || month > 12) {
        _result = false;
    }
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day < 1 || day > 31)) {
        _result = false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day < 1 || day > 30)) {
        _result = false;
    }
    if (month == 2 && (day < 1 || day > 29)) {
        _result = false;
    }

    assert(func(_result));
    return _result;
}