#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Function prototypes
int count_characters(const char* filename);
int count_words(const char* filename);

int main(int argc, char* argv[]) {
    
}

// Function to count characters in a file
int count_characters(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        return -1; // Return -1 if the file cannot be opened
    }

    int char_count = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        char_count++;
    }

    fclose(file);
    return char_count;
}

// Function to count words in a file
int count_words(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        return -1; // Return -1 if the file cannot be opened
    }

    int word_count = 0;
    int in_word = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        }
        else {
            in_word = 1;
        }
    }

    // If the last character was part of a word, count it as a word
    if (in_word) {
        word_count++;
    }

    fclose(file);
    return word_count;
}
