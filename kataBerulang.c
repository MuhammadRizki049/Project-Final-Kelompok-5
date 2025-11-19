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
    
    if (word_index > 0) {
        current_word[word_index] = '\0';
        add_unique_word(current_word);
    }
}

int main() {
    FILE *f_in, *f_out;
    char line[MAX_LINE_LENGTH];

    f_in = fopen("lirik.txt", "r");
    if (f_in == NULL) {
        perror("Error: Tidak dapat membuka file 'lirik.txt'");
        printf("Pastikan Anda sudah membuat file lirik.txt di folder yang sama.\n");
        return 1; 
    }

     f_out = fopen("kosa-kata.word", "w");
    if (f_out == NULL) {
        perror("Error: Tidak dapat membuat file 'kosa-kata.word'");
        fclose(f_in); 
        return 1;
    }

    if (fgets(line, MAX_LINE_LENGTH, f_in) != NULL) {
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0; 
        
        fprintf(f_out, "%s\n", line); 
    } else {
        fprintf(stderr, "Error: File input 'lirik.txt' kosong.\n");
        fclose(f_in);
        fclose(f_out);
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, f_in) != NULL) {
        process_line(line);
    }

    for (int i = 0; i < unique_word_count; i++) {
        fprintf(f_out, "%s=\n", unique_words[i]);
    }

    fclose(f_in);
    fclose(f_out);

    printf("Berhasil! File 'kosa-kata.word' telah dibuat dengan daftar kosa kata unik.\n");
    return 0;
}
        
