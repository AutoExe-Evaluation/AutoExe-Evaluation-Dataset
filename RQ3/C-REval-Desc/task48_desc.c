#include <stdio.h>
#include <string.h>

int is_palindrome(int n) {
    char str[12];
    sprintf(str, "%d", n);
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void even_odd_palindrome(int n) {
    int even_palindrome_count = 0;
    int odd_palindrome_count = 0;

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1 && is_palindrome(i)) {
            odd_palindrome_count++;
        } else if (i % 2 == 0 && is_palindrome(i)) {
            even_palindrome_count++;
        }
    }

    int result[2] = {even_palindrome_count, odd_palindrome_count};

    // assert(func(result)); // Postcondition placeholder
}