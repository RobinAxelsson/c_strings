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
    int wordCount = 0;
    char last = ' ';

    for (char* c = text; *c != '\0' ; c++) {
        if(*c != ' ' && *c != '\n' && (last == ' ' || last == '\n'))
            wordCount++;
        last = *c;
    }

    return wordCount;
}

int str_paragraph_count(const char* text) {
    int paraCount = 0;
    char last = '\n';

    for (char* c = text; *c != '\0' ; c++) {
        if(*c != ' ' && *c != '\n' && (last == '\n'))
            paraCount++;
        last = *c;
    }
    return paraCount;
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

char*** doc_get_paragraphs(char* text){

}

char** doc_get_words(char* text){
    int wordCount = str_word_count(text);
    char** words = malloc(sizeof(char*) * wordCount);
    char* textPtr = text;

    for (int i = 0; i < wordCount; ++i) {
        while(*textPtr == ' ' || *textPtr == '\n') textPtr++;
        if(*textPtr == '\0') break;

        char* w_start = textPtr;
        char* w_end = textPtr;
        while(*textPtr != ' ' && *textPtr != '\n'){
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