#include <stdio.h>
#include <string.h>

char** total_match(char** lst1, int len1, char** lst2, int len2) {
    int l1 = 0;
    for (int i = 0; i < len1; i++) {
        l1 += strlen(lst1[i]);
    }

    int l2 = 0;
    for (int i = 0; i < len2; i++) {
        l2 += strlen(lst2[i]);
    }

    char** _result;
    if (l1 <= l2) {
        _result = lst1;
    } else {
        _result = lst2;
    }

    // Assume func is defined elsewhere and checks the condition.
    assert(func(_result)); 
    return _result;
}