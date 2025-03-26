#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main() {
    char s[MAX];
    scanf("%s", s);
    
    char stack[MAX];
    int top = -1;

    // PRE: The input string consists only of '+' and '-' characters.
    assert(s[0] == '+' || s[0] == '-'); // PRE: Input must be valid.

    for(int i = 0; s[i] != '\0'; ++i) {
        if(top == -1) {
            stack[++top] = s[i];
        } else if(s[i] != stack[top]) {
            stack[++top] = s[i];
        } else {
            top--;
        }
    }
    
    // POST: The wires can be untangled if the stack is empty at the end.
    assert(top == -1 || top >= 0); // POST: The result is correctly determined based on the stack state.

    if(top == -1)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}