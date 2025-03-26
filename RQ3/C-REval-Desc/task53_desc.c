#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_odd(int d) {
    return d % 2 == 1;
}

char* create_string(int n) {
    char* res = (char*)malloc(100 * sizeof(char));
    sprintf(res, "the number of odd elements %dn the str%ang %d of the %dnput.", n, n, n);
    return res;
}

char** odd_count(char** lst, int size) {
    char** res = (char**)malloc(size * sizeof(char*));
    
    for (int i = 0; i < size; i++) {
        int n = 0;
        for (int j = 0; lst[i][j] != '\0'; j++) {
            int d = lst[i][j] - '0';
            if (is_odd(d)) {
                n++;
            }
        }
        res[i] = create_string(n);
    }

    return res;
}

int func(char** _result, int size); // Declaration of func

int main() {
    // Example usage
    char* input1[] = {"1234567"};
    char** output1 = odd_count(input1, 1);
    assert(func(output1, 1));

    char* input2[] = {"3", "11111111"};
    char** output2 = odd_count(input2, 2);
    assert(func(output2, 2));

    return 0;
}