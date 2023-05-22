//
// Created by robin.salihaxelsson on 2023-05-22.
//

#include "strings_r.h"
#include <stdlib.h>

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
    int sentenceCount = 0;

    for (char* c = text; *c != '\0' ; c++) {
        int isDelimiter = *c == '.' || *c == '!' || *c == '?';
        if(isDelimiter){
            sentenceCount++;
            while(*(c + 1) == '.' || *(c + 1) == '!' || *(c + 1) == '?'){
                if(*(c + 1) == '\0'){
                    break;
                }
                c++;
            }
        }
    }
    return sentenceCount;
}

char** doc_get_paragraphs(char* text){
    int paragraphCount = str_paragraph_count(text);
    char** paragraphs = malloc(sizeof(char*) * paragraphCount);
    char* textPtr = text;

    for (int i = 0; i < paragraphCount; ++i) {
        while(*textPtr == '\n') textPtr++;
        if(*textPtr == '\0') break;

        char* w_start = textPtr;
        char* w_end = textPtr;
        while(*textPtr != '\n' && *textPtr != '\0'){
            textPtr++;
            w_end++;
        }
        int length = w_end - w_start;
        paragraphs[i] = malloc(sizeof(char) * (length + 1));
        for (int j = 0; j < length; ++j) {
            paragraphs[i][j] = *(w_start + j);
        }
        paragraphs[i][length] = '\0';
    }
    return paragraphs;
}

int char_is_delimiter(char character, char* delimiters){
    for (char* c = delimiters; *c != '\0' ; c++) {
        if(character == *c) return 1;
    }
    return 0;
}

int str_split_count(char* text, char* delimiters){
    if(*text == '\0' || text == NULL) return 0;
    int splits = 1;
    char* txtPtr = text;

    while (*(txtPtr + 1) != '\0'){
        int currentIsDelimiter = char_is_delimiter(*txtPtr, delimiters);
        int nextIsDelimiter = char_is_delimiter(*(txtPtr + 1), delimiters);

        if(!currentIsDelimiter && nextIsDelimiter){
            splits++;
        }
        txtPtr++;
    }
    return splits;
}

char** doc_get_words(const char* text){
    int wordCount = str_word_count(text);
    char** words = malloc(sizeof(char**) * wordCount);
    char* textPtr = text;

    for (int i = 0; i < wordCount; ++i) {
        while(*textPtr == ' ' || *textPtr == '\n') textPtr++;
        if(*textPtr == '\0') break;

        char* w_start = textPtr;
        char* w_end = textPtr;
        while(*textPtr != ' ' && *textPtr != '\n' && *textPtr != '\0'){
            w_end++;
            textPtr++;
        }
        int length = w_end - w_start;
        words[i] = malloc(sizeof(char) * (length + 1));
        for (int j = 0; j < length; ++j) {
            words[i][j] = *(w_start + j);
        }
        words[i][length] = '\0';
    }

    return words;
};