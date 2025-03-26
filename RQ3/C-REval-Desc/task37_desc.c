#include <string.h>
#include <stdbool.h>
#include <assert.h>

bool func(bool result);

bool prime_length(char *string) {
    int l = strlen(string);
    bool _result = true;
    if (l == 0 || l == 1) {
        _result = false;
    }
    for (int i = 2; i < l; i++) {
        if (l % i == 0) {
            _result = false;
        }
    }

    assert(func(_result));
    return _result;
}