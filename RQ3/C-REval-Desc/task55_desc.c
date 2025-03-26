#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** select_words(const char* s, int n, int* return_size) {
    char** result = malloc(100 * sizeof(char*)); // assuming max 100 words
    *return_size = 0;
    char* str = strdup(s);
    char* word = strtok(str, " ");
    
    while (word != NULL) {
        int n_consonants = 0;
        for (int i = 0; i < strlen(word); i++) {
            if (tolower(word[i]) != 'a' && tolower(word[i]) != 'e' && tolower(word[i]) != 'i' && 
                tolower(word[i]) != 'o' && tolower(word[i]) != 'u') {
                n_consonants++;
            }
        }
        if (n_consonants == n) {
            result[*return_size] = strdup(word);
            (*return_size)++;
        }
        word = strtok(NULL, " ");
    }
    
    free(str);
    
    return result;
}

// Example usage
// Call select_words with appropriate parameters and assert the condition for func.