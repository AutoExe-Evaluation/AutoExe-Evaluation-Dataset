#include <stdbool.h>
#include <string.h>

bool func(bool result);

void correct_bracketing(const char* brackets) {
    int depth = 0;
    bool _result = true;
    int length = strlen(brackets);
    
    for (int i = 0; i < length; i++) {
        char b = brackets[i];
        if (b == '<') {
            depth++;
        } else {
            depth--;
        }
        if (depth < 0) {
            _result = false;
        }
    }
    if (_result) {
        _result = (depth == 0);
    }

    func(_result);
}