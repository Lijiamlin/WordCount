#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Function prototypes
int count_characters(const char* filename);
int count_words(const char* filename);

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-C|-W] [input_file_name]\n", argv[0]);
        return 1;
    }

  

    // Determine the operation based on the parameter
    if (strcmp(argv[1], "-C") == 0) {
        int char_count = count_characters(argv[2]);
        if (char_count >= 0) {
            printf("字符数：%d\n", char_count);
        }
        else {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
    }
    else if (strcmp(argv[1], "-W") == 0) {
        int word_count = count_words(argv[2]);
        if (word_count >= 0) {
            printf("单词数：%d\n", word_count);
        }
        else {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
    }
    else {
        fprintf(stderr, "Invalid parameter. Use -C for character count or -W for word count.\n");
        return 1;
    }

    return 0;
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
