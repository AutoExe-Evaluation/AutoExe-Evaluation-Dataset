#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int func(const char *str);

char* words_in_sentence(const char *sentence) {
    char *new_lst = (char *)malloc(100 * sizeof(char));
    new_lst[0] = '\0';
    char *word;
    char *sentence_copy = strdup(sentence);
    word = strtok(sentence_copy, " ");
    
    while (word != NULL) {
        int flg = 0;
        int len_word = strlen(word);
        if (len_word == 1) {
            flg = 1;
        }
        for (int i = 2; i < len_word; i++) {
            if (len_word % i == 0) {
                flg = 1;
                break;
            }
        }
        if (flg == 0 || len_word == 2) {
            if (strlen(new_lst) > 0) {
                strcat(new_lst, " ");
            }
            strcat(new_lst, word);
        }
        word = strtok(NULL, " ");
    }
    
    free(sentence_copy);
    
    assert(func(new_lst));
    
    return new_lst;
}