//
// Created by robin.salihaxelsson on 2023-05-22.
//

#include "strings_r.h"
#include <stdlib.h>

int str_split_count(char* text, char* delimiters){
    if(*text == '\0' || text == NULL) return 0;
    int splits = 1;
    char* txtPtr = text;

    while (*(txtPtr + 1) != '\0'){
        char current = *txtPtr;
        char next = *(txtPtr + 1);
        int currentIsDelimiter = char_is_delimiter(current, delimiters);
        int nextIsDelimiter = char_is_delimiter(next, delimiters);

        if(currentIsDelimiter && !nextIsDelimiter){
            splits++;
        }
        txtPtr++;
    }
    return splits;
}

char** str_splitr(const char* text, char* delimiters, char terminator){
    int splitLength = str_split_count(text, delimiters);
    char* txtPtr = text;
    char** substrings = malloc(sizeof(char*) * (splitLength + 1));
    substrings[splitLength] = NULL;

    for (int i = 0; i < splitLength; ++i) {
        int length = 0;
        while(char_is_delimiter(*txtPtr, delimiters) && *txtPtr != terminator){
            txtPtr++;
        }
        char* start = txtPtr;
        while(!char_is_delimiter(*txtPtr, delimiters) && *txtPtr != terminator){
            length++;
            txtPtr++;
        }
        substrings[i] = malloc(sizeof(char) * (length + 1));

        for (int j = 0; j < length; ++j) {
            substrings[i][j] = *(start + j);
        }
        substrings[i][length] = '\0';
    }

    return substrings;
}

char**** get_document(char* text){
    char**** document;
    char** newlineSplit = str_splitr(text, "\n", '\0');
    int p_length = 0;
    for (char** cpp = newlineSplit; *cpp != NULL ; cpp++) p_length++;
    document = malloc(sizeof(char***) * (p_length + 1));
    document[p_length] = NULL;


    for (int i = 0; i < p_length; ++i) {
        char** dotSplit = str_splitr(newlineSplit[i], ".!?\n", '\0');
        int s_length = 0;
        for (char** cpp = dotSplit; *cpp != NULL ; cpp++) s_length++;
        document[i] = malloc(sizeof(char**) * (s_length + 1));
        document[i][s_length] = NULL;

        for (int j = 0; j < s_length; ++j) {
            char** words = str_splitr(newlineSplit[i], " ", '\0');
            int w_length = 0;
            for (char** cpp = dotSplit; *cpp != NULL ; cpp++) w_length++;
            document[i][j] = malloc(sizeof(char*) * (w_length + 1));
            document[i][j][s_length] = NULL;

            for (int k = 0; k < w_length; ++k) {
                int length = str_length(words[k]);
                document[i][j][k] = malloc(sizeof(char) * (length + 1));
                str_copy(words[k], document[i][j][k]);
                free(words[k]);
            }
            free(words);
        }
        free(dotSplit);
    }
    free(newlineSplit);

    return document;
}

int str_length(const char* string){
    int count = 0;
    for (char* c = string; *c != '\0'; c++) count++;
    return count;
}

int str_word_count(const char* text) {
    return str_split_count(text, " \n");
}

int str_paragraph_count(const char* text) {
    return str_split_count(text, "\n");
}


char* str_to_upper(const char* string){
    int length = str_length(string);
    char* newString = malloc(sizeof(char)* (length+1));
    if(newString == NULL){
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        if('a' <= string[i] && string[i] <= 'z' ){
            newString[i] = string[i] -'a' + 'A';
        }
        else newString[i] = string[i];
    }
    newString[length] = '\0';

    return newString;
}

char* str_to_lower_copy(const char* string){
    int length = str_length(string);
    char* newString = malloc(sizeof(char)* (length+1));

    if(newString == NULL){
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        if('A' < string[i] && string[i] < 'Z' ){
            newString[i] = string[i] + 'a' - 'A';
        }
        else newString[i] = string[i];
    }
    newString[length] = '\0';

    return newString;
}

void str_to_lower_in_place(char* string){
    int length = str_length(string);

    for (int i = 0; i < length; ++i) {
        if('A' <= string[i] && string[i] <= 'Z'){
            string[i] = string[i] + 'a' - 'A';
        }
    }
}

int str_equal(char* strA, char* strB){
    if(strA == strB) return 1;
    if(*strA == '\0' && *strB == '\0') return 1;
    int count = str_length(strA);
    if(count != str_length(strB)) return 0;

    for (int i = 0; i < count; ++i) {
        if(strA[i] != strB[i]){
            return 0;
        }
    }
    return 1;
}

void str_copy(char* source, char* target){
    char* targetPtr = target;
    char* sourcePtr = source;
    do {
        *targetPtr = *sourcePtr;
        targetPtr++;
        sourcePtr++;
    } while(*sourcePtr != '\0');

    *targetPtr = '\0';
}

void str_reverse(char* string, char* reverse){
    int length = str_length(string);
    int swaps = length / 2;

    if(length % 2 == 1){
        reverse[swaps] = string[swaps];
    }

    for (int i = 0; i < swaps; ++i) {
        char start = string[i];
        char end = string[length - i - 1];
        reverse[i] = end;
        reverse[length - i - 1] = start;
    }
    reverse[length + 1] = '\0';
}

int str_sentence_count(const char* text) {
    return str_split_count(text, ".!?\n");
}

char** doc_get_paragraphs(char* text){
    return str_splitr(text, "\n", '\0');
}

int char_is_delimiter(char character, char* delimiters){
    for (char* c = delimiters; *c != '\0' ; c++) {
        if(character == *c) return 1;
    }
    return 0;
}

char** doc_get_words(const char* text){
    return str_splitr(text, " ", '\0');
};