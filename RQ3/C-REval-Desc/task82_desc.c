#include <stdio.h>
#include <string.h>

void int_to_mini_roman(int number, char *result) {
    int num[] = {1, 4, 5, 9, 10, 40, 50, 90,  
                 100, 400, 500, 900, 1000}; 
    char *sym[] = {"I", "IV", "V", "IX", "X", "XL",  
                   "L", "XC", "C", "CD", "D", "CM", "M"}; 
    int i = 12;
    result[0] = '\0'; 
    while (number) { 
        int div = number / num[i]; 
        number %= num[i]; 
        while (div) { 
            strcat(result, sym[i]); 
            div -= 1; 
        } 
        i -= 1; 
    } 
    for (int j = 0; result[j]; j++) {
        result[j] = tolower(result[j]);
    }
} 

int func(const char *s); // Assume func is defined elsewhere

int main() {
    char result[100];
    int_to_mini_roman(19, result);
    assert(func(result));
    int_to_mini_roman(152, result);
    assert(func(result));
    int_to_mini_roman(426, result);
    assert(func(result));
    return 0;
}