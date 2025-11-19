#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  
#include <ctype.h> 

#define MAX_LINE_LENGTH 1024  
#define MAX_WORD_LENGTH 100  
#define MAX_UNIQUE_WORDS 5000 

char unique_words[MAX_UNIQUE_WORDS][MAX_WORD_LENGTH];
int unique_word_count = 0;

int is_word_char(char c) {
    return isalpha(c) || c == '\'';
}

