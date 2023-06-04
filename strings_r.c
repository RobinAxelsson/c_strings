//
// Created by robin.salihaxelsson on 2023-05-22.
//

#include "strings_r.h"
#include <string.h>
#include <stdlib.h>

int count_tokens(const char* text, const char* delimiters){
    int token_count = 0;
    char *buffer = strdup(text);
    if(buffer == NULL) return  -1;
    char *sp;
    char *token = strtok_r(buffer, delimiters, &sp);
    while(token != NULL){
        token_count++;
        token = strtok_r(NULL, delimiters, &sp);
    }
    free(buffer);
    return token_count;
}

struct document get_document_struct(const char* text){
    struct document result;
    result.paragraph_count = count_tokens(text, "\n");
    int p_count = count_tokens(text, "\n");
    result.data = malloc(sizeof(struct paragraph) * result.paragraph_count);
    if(result.data == NULL){
        struct document error = { .data = NULL, .paragraph_count = -1 };
    }
    char *buffer = strdup(text);
    char *sp;
    char *token = strtok_r(buffer, "\n", &sp);

    for (int i = 0; i < p_count; ++i) {
        struct paragraph paragraph = get_paragraph_struct(token);
        result.data[i] = paragraph;
        token = strtok_r(NULL, "\n", &sp);
        if(token == NULL) break;
    }
    free(buffer);
    return result;
}

struct paragraph get_paragraph_struct(const char* text){
    struct paragraph result;
    int s_count = count_tokens(text, ".");
    result.data = malloc(sizeof(struct sentence) * s_count);
    if(result.data == NULL){
        struct paragraph error = { .data = NULL, .sentence_count = -1 };
        return error;
    }
    char *buffer = strdup(text);
    char *sp;
    char *token = strtok_r(buffer, ".", &sp);

    for (int i = 0; i < s_count; ++i) {
        struct sentence sentence = get_sentence_struct(token);
        result.data[i] = sentence;
        token = strtok_r(NULL, ".", &sp);
        if(token == NULL) break;
    }

    free(buffer);
    return result;
}

struct sentence get_sentence_struct(const char* text){
    struct sentence result;
    int w_count = count_tokens(text, " ");
    result.word_count = w_count;
    result.data = malloc(sizeof(struct word) * w_count);
    if(result.data == NULL){
        struct sentence s = { .data = NULL, .word_count = -1 };
        return s;
    };

    char *buffer = strdup(text);
    char *sp;
    char *token = strtok_r(buffer, " ", &sp);

    for (int i = 0; i < w_count; ++i) {
        struct word word = get_word_struct(token);
        result.data[i] = word;
        token = strtok_r(NULL, " ", &sp);
    }
    free(buffer);
    return result;
}

struct word get_word_struct(const char* chars){
    struct word word;
    word.data = strdup(chars);
    return word;
}

int str_split_count(char* text, char* delimiters){
    if(text == NULL || *text == '\0') return 0;
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

char** str_splitr(char* text, char* delimiters, char terminator){
    if (text == NULL || delimiters == NULL) return NULL;

    int splitLength = str_split_count(text, delimiters);
    char* txtPtr = text;

    char** substrings = malloc(sizeof(char*) * (splitLength + 1));
    if (substrings == NULL) return NULL;

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
        if (substrings[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(substrings[j]);
            }
            free(substrings);
            return NULL;
        }

        for (int j = 0; j < length; ++j) {
            substrings[i][j] = *(start + j);
        }
        substrings[i][length] = '\0';
    }

    return substrings;
}

char* str_left_trim(char* source, char* characters){
    if(source == NULL) return NULL;
    if(source[0] == '\0') return NULL;
    if(characters == NULL) return source;
    char* startPtr = source;
    while(char_is_delimiter(*startPtr, characters)) {
        startPtr++;
    }

    return startPtr;
}

char* str_right_trim(char* source, char* characters){
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
        if (arr == NULL) return NULL;
        arr[0] = *startPtr;
        arr[1] = '\0';

        return arr;
    }

    size_t resultLength = endPtr - startPtr + 1;
    char* result = malloc(sizeof(char) * (endPtr - startPtr + 1));
    if(result == NULL) return NULL;

    result[resultLength] = '\0';

    for (int i = 0; i < resultLength; ++i) {
        result[i] = startPtr[i];
    }

    return result;
}

char* str_trim(char* source, char* characters){
    return str_right_trim(str_left_trim(source, characters), characters);
}

char*** get_sentences(char* text){
    if(text == NULL) return NULL;

    char** sentences = str_splitr(text, ".!?", '\0');
    if(sentences == NULL) return NULL;

    int sentences_count = 0;
    for (char** cpp = sentences; *cpp != NULL ; cpp++) sentences_count++;

    char*** sentenceList = malloc(sizeof(char**)*(sentences_count + 1));
    if(sentenceList == NULL) return NULL;
    sentenceList[sentences_count] = NULL;

    for (int i = 0; i < sentences_count; ++i) {
        char** words = str_splitr(sentences[i], " \n", '\0');
        if(words == NULL) continue;

        int word_count = 0;
        for (char** cpp = words; *cpp != NULL ; cpp++) word_count++;

        sentenceList[i] = malloc(sizeof(char*)* (word_count + 1));
        if(sentenceList[i] == NULL) continue;
        sentenceList[i][word_count] = NULL;

        for (int j = 0; j < word_count; ++j) {
            int wordLength = str_length(words[j]);
            sentenceList[i][j] = malloc(sizeof(char) * (wordLength + 1));
            str_copy(words[j], sentenceList[i][j]);
            free(words[j]);
        }
        free(words);
    }
    free(sentences);

    return sentenceList;
}

int countArray(void **ptr){
    if(ptr == NULL) return 0;
    int count = 0;
    while (*ptr != NULL) {
        count++;
        ptr++;
    }
    return count;
}

char**** get_document(char* text){
    if(text == NULL) return NULL;
    if(*text == '\0') return NULL;

    char** paragraphs = str_splitr(text, "\n", '\0');
    int paragraph_count = countArray((void*)paragraphs);
    char**** document = malloc(sizeof(char***) * (paragraph_count + 1));
    document[paragraph_count] = NULL;

    for (int i = 0; i < paragraph_count; ++i) {
        char** sentences = str_splitr(paragraphs[i], ".!?", '\0');
        int sentencesCount = countArray((void*)sentences);
        document[i] = malloc(sizeof(char**) * (sentencesCount + 1));
        document[i][sentencesCount] = NULL;

        for (int j = 0; j < sentencesCount; ++j) {
            char** wordList = str_splitr(sentences[j], " ", '\0');
            int word_count = countArray((void*)wordList);
            document[i][j] = malloc(sizeof(char*)* (word_count + 1));
            document[i][j][word_count] = NULL;

            for (int k = 0; k < word_count; ++k) {
                char* word = wordList[k];
                int word_length = str_length(word);
                document[i][j][k] = malloc(sizeof(char) * (word_length + 1));
                str_copy(word, document[i][j][k]);
                free(wordList[k]);
            }
            free(wordList);
            free(sentences[j]);
        }
        free(sentences);
        free(paragraphs[i]);
    }
    free(paragraphs);

    return document;
}

void free_2dArr(char** words){
    if(words == NULL) return;
    int w_count = countArray((void*) words);
    for (int i = 0; i < w_count; ++i) {
        free(words[i]);
    }
    free(words);
}

void free_Array(void** arr){
    if(arr == NULL) return;
    int count = countArray((void*) arr);
    for (int i = 0; i < count; ++i) {
        free(arr[i]);
    }
    free(arr);
}

void free_array_rec(void **ptr, int recursions) {
    if (ptr == NULL) {
        return;
    }
    int count = countArray((void*)ptr);
    for (int i = 0; i < count; ++i) {
        if(ptr[i] == NULL) continue;
        if(recursions != 0){
            free_array_rec((void**)ptr[i], recursions -1);
        }
        free(ptr[i]);
    }
    free(ptr);
}

void free_document(char**** document){
    if(document == NULL) return;
    int paragraph_count = countArray((void **)document);
    for (int i = 0; i < paragraph_count; ++i) {
        if(document[i] == NULL) continue;
        int sentence_count = countArray((void **)document[i]);
        for (int j = 0; j < sentence_count; ++j) {
            if(document[i][j] == NULL) continue;
            int word_count = countArray((void **)document[i][j]);
            for (int k = 0; k < word_count; ++k) {
                if(document[i][j][k] == NULL) continue;
                free(document[i][j][k]);
            }
            free(document[i][j]);
        }
        free(document[i]);
    }
    free(document);
}

int str_length(char* string){
    if(string == NULL) return 0;
    int count = 0;
    for (char* c = string; *c != '\0'; c++) count++;
    return count;
}

int str_word_count(char* text) {
    return str_split_count(text, " \n");
}

int str_paragraph_count(char* text) {
    return str_split_count(text, "\n");
}


char* str_to_upper(char* string){
    int length = str_length(string);
    char* newString = malloc(sizeof(char)* (length+1));
    if(newString == NULL){
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        if('a' <= string[i] && string[i] <= 'z' ){
            newString[i] = (char) (string[i] -'a' + 'A');
        }
        else newString[i] = string[i];
    }
    newString[length] = '\0';

    return newString;
}

char* str_to_lower(char* string){
    int length = str_length(string);
    char* newString = malloc(sizeof(char)* (length+1));

    if(newString == NULL){
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        if('A' <= string[i] && string[i] <= 'Z' ){
            newString[i] = (char) (string[i] + 'a' - 'A');
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
            string[i] = (char)(string[i] + 'a' - 'A');
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

int str_sentence_count(char* text) {
    return str_split_count(text, ".!?\n");
}

char** doc_get_paragraphs(char* text){
    return str_splitr(text, "\n", '\0');
}

int char_is_delimiter(char character, char* delimiters){
    if (delimiters == NULL) {
        return 0;
    }

    for (char* c = delimiters; *c != '\0' ; c++) {
        if(character == *c) {
            return 1;
        }
    }

    return 0;
}

char** doc_get_words(char* text){
    return str_splitr(text, " ", '\0');
};

//