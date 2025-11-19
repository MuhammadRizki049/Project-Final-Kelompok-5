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

void add_unique_word(char* word) {
    for (int i = 0; i < unique_word_count; i++) {
        if (strcmp(unique_words[i], word) == 0) {
            return; 
        }
    }

    if (unique_word_count < MAX_UNIQUE_WORDS) {
        strcpy(unique_words[unique_word_count], word);
        unique_word_count++;
    } else {
        fprintf(stderr, "Peringatan: Jumlah kata unik maksimum (%d) telah tercapai.\n", MAX_UNIQUE_WORDS);
    }
}

void process_line(char* line) {
    char current_word[MAX_WORD_LENGTH];
    int word_index = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char c = tolower(line[i]); 
        if (is_word_char(c)) {
            if (word_index < MAX_WORD_LENGTH - 1) {
                current_word[word_index++] = c;
            }
        } else {
            if (word_index > 0) {
                current_word[word_index] = '\0'; 
                add_unique_word(current_word);
                word_index = 0; 
            }
        }
    }
    
