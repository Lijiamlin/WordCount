#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 函数名
int count_characters(const char* filename);
int count_words(const char* filename);

int main(int argc, char* argv[]) {
    // 检查是否提供了正确数量的参数
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-C|-W] [input_file_name]\n", argv[0]);
        return 1;
    }

  

    // 根据参数确定操作
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

// 统计文件中字符数
int count_characters(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        return -1; // 若文件无法被打开则返回-1
    }

    int char_count = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        char_count++;
    }

    fclose(file);
    return char_count;
}

// 统计单词数
int count_words(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        return -1; // 若文件无法被打开则返回-1
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

    // 如果最后一个字符是单词的一部分，则将其计为单词
    if (in_word) {
        word_count++;
    }

    fclose(file);
    return word_count;
}
