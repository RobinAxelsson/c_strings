#include <stdio.h>
#include <malloc.h>

typedef void* (*Func)(void*);

int str_count(const char* string){
    int count = 0;
    while(*string != '\0'){
        string++;
        count++;
    }
    return count;
}

int str_word_count(const char* text) {
    int wordCount = 0;

    if(*text == '\0') return 0;

    while (*text != '\0') {
        if (*text == ' ' || *text == '\n') {
            wordCount++;
        }
        text++;
    }
    wordCount++;
    return wordCount;
}

char* str_to_upper(char* string){
    int length = str_count(string);
    char* newString = malloc(sizeof(char)*length+1);

    for (int i = 0; i < length; ++i) {
        if(96 < string[i] && string[i] < 123 ){
            newString[i] = string[i] - 32;
        }
        else newString[i] = string[i];
    }
    newString[length] = '\0';

    return newString;
}

char* str_to_lower(char* string){
    int length = str_count(string);
    char* newString = malloc(sizeof(char)*length+1);

    for (int i = 0; i < length; ++i) {
        if(64 < string[i] && string[i] < 91 ){
            newString[i] = string[i] + 32;
        }
        else newString[i] = string[i];
    }
    newString[length] = '\0';

    return newString;
}

int str_equal(char* strA, char* strB){
    if(strA == strB) return 1;
    if(*strA == '\n' && *strB == '\n') return 1;
    int count = str_count(strA);
    if(count != str_count(strB)) return 0;

    for (int i = 0; i < count; ++i) {
        if(strA[i] != strB[i]){
            return 0;
        }
    }
    return 1;
}

void TestIntResult(Func func, char* testName, void* data, int expected, int* tests, int* passed){
    (*tests)++;

    int result = (int)func(data);
    if(expected == result){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expected: %d, result: %d\n", testName, expected, result);
    }
}

void TestStrResult(Func func, char* testName, void* data, char* expected, int* tests, int* passed){
    (*tests)++;

    char* result = (char*)func(data);
    if(str_equal(expected, result)){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expected: %s, result: %s\n", testName, expected, result);
    }
}

int main() {
    int tests = 0;
    int passed = 0;

    TestIntResult((Func) str_word_count, "count_words__3_words__3", "Hello counting words", 3, &tests, &passed);
    TestIntResult((Func) str_word_count, "count_words__5_words_newline__5", "Hello world!\nYou are great", 5, &tests,
                  &passed);
    TestIntResult((Func) str_word_count, "count_words__0_words__0", "", 0, &tests, &passed);
    TestIntResult((Func) str_count, "count_chars__words__5", "abcde", 5, &tests, &passed);
    TestIntResult((Func) str_count, "count_chars__empty__5", "", 0, &tests, &passed);

    TestStrResult((Func)str_to_upper, "to upper 1","HELLO WORLD", "HELLO WORLD", &tests, &passed);
    TestStrResult((Func)str_to_upper, "to upper 2","hello world", "HELLO WORLD", &tests, &passed);
    TestStrResult((Func)str_to_upper, "to upper 3","hello !Wld...", "HELLO !WLD...", &tests, &passed);
    TestStrResult((Func)str_to_lower, "to lower 1","Hello !Wld...", "hello !wld...", &tests, &passed);
    printf("%d/%d tests passed", passed, tests);
    return 0;
}