#include <stdio.h>
#include <stdlib.h>

void func(int result[2]);

void even_odd_count(int num) {
    int even_count = 0;
    int odd_count = 0;
    num = abs(num);
    
    while (num > 0) {
        int digit = num % 10;
        if (digit % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
        num /= 10;
    }
    
    int result[2] = {even_count, odd_count};
    
    func(result); // POST: func is equivalent to: Given an integer. return a tuple that has the number of even and odd digits respectively.
}