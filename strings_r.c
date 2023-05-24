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

char* str_left_trim(char* const source, char* const characters){
    if(source == NULL) return NULL;
    if(source[0] == '\0') return NULL;
    if(characters == NULL) return source;
    char* startPtr = source;
    while(char_is_delimiter(*startPtr, characters)) {
        startPtr++;
    }

    return startPtr;
}

char* str_right_trim(char* const source, char* const characters){
    if(source == NULL) return NULL;
    if(source[0] == '\0') return NULL;
    if(characters == NULL) return source;

    char* startPtr = source;
    int sourceLength = str_length(source);
    char* endPtr = startPtr + sourceLength - 1;
    while(char_is_delimiter(*endPtr, characters)) {
        endPtr--;
    }
    if(startPtr == endPtr){
        char* arr = malloc(sizeof(char) * 2);
        arr[0] = *startPtr;
        arr[1] = '\0';

        return arr;
    }

    int resultLength = endPtr - startPtr + 1;
    char* result = malloc(sizeof(char) * (endPtr - startPtr + 1));
    result[resultLength] = '\0';

    for (int i = 0; i < resultLength; ++i) {
        result[i] = startPtr[i];
    }

    return result;
}

char* str_trim(char* const source, char* const characters){
    return str_right_trim(str_left_trim(source, characters), characters);
}

char*** get_sentences(char* text){
    char*** sentenceList;
    char** dotSplit = str_splitr(text, ".!?", '\0');
    int s_count = 0;
    for (char** cpp = dotSplit; *cpp != NULL ; cpp++) s_count++;

    sentenceList = malloc(sizeof(char**)*(s_count + 1));
    sentenceList[s_count] = NULL;

    for (int i = 0; i < s_count; ++i) {
        char** wordSplit = str_splitr(dotSplit[i], " \n", '\0');
        int w_count = 0;
        for (char** cpp = wordSplit; *cpp != NULL ; cpp++) w_count++;
        sentenceList[i] = malloc(sizeof(char*)* (w_count + 1));
        sentenceList[i][w_count] = NULL;

        for (int j = 0; j < w_count; ++j) {
            int wordLength = str_length(wordSplit[j]);
            sentenceList[i][j] = malloc(sizeof(char) * (wordLength + 1));
            str_copy(wordSplit[j], sentenceList[i][j]);
        }
    }

    return sentenceList;
}

int count_grouped_strings(char** grouped){
    int count = 0;
    while()
}

char**** get_document(char* text){
    if(text == NULL) return NULL;
    if(*text == '\0') return NULL;

    char** paragraphs = str_splitr(text, "\n", '\0');
    int paragraph_count = 0;
    char**** document = malloc(sizeof(char***));

    char*** paragraph0 = malloc(sizeof(char**) * 2);
    document[0] = paragraph0;

        char** sentence0 = malloc(sizeof(char*) * 2);
        paragraph0[0] = sentence0;
        char* word0 = malloc(sizeof(char) * 6);
        sentence0[0] = word0;
        char* word1 = malloc(sizeof(char) * 6);
        sentence0[1] = word1;
        str_copy("Hello", word0);
        str_copy("World", word1);

        char** sentence1 = malloc(sizeof(char*));
        paragraph0[1] = sentence1;
        char* word10 = malloc(sizeof(char)*4);
        sentence1[0] = word10;
        str_copy("Hey", word10);

    char*** paragraph1 = malloc(sizeof(char**) * 1);
    document[1] = paragraph1;

        char** sentence10 = malloc(sizeof(char*));
        paragraph1[0] = sentence10;
        char* word100 = malloc(sizeof(char) * 8);
        sentence10[0] = word100;
        str_copy("newline", word100);

    return document;
}

int str_length(const char* string){
    if(string == NULL) return 0;
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
    if(strA == NULL || strB == NULL) return 0;
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