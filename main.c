#include <stdio.h>
#include <malloc.h>

typedef void* (*Func)(void*);
typedef void* (*FuncNoArgs)();


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

char* str_to_lower_copy(char* string){
    int length = str_count(string);
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
    int length = str_count(string);

    for (int i = 0; i < length; ++i) {
        if('A' <= string[i] && string[i] <= 'Z'){
            string[i] = string[i] + 'a' - 'A';
        }
    }
}

int str_equal(char* strA, char* strB){
    if(strA == strB) return 1;
    if(*strA == '\0' && *strB == '\0') return 1;
    int count = str_count(strA);
    if(count != str_count(strB)) return 0;

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
    int length = str_count(string);
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

int test_str_copy_hello(){
    char* source = "Hello";
    char target[6];
    str_copy(source, target);
    return str_equal(source, target);
}

int test_str_copy_hell(){
    char* source = "Hell";
    char target[6];
    str_copy(source, target);
    return str_equal(source, target);
}

int test_str_reverse_Abc(){
    char* source = "Abc";
    char target[4];
    str_reverse(source, target);
    return str_equal("cbA", target);
}


void TestBoolResult(FuncNoArgs func, char* testName, int expectedBool, int* tests, int* passed){
    (*tests)++;

    int result = (int)func();
    if(expectedBool == result){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expectedBool: %d, result: %d\n", testName, expectedBool, result);
    }
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
    TestStrResult((Func)str_to_lower_copy, "to lower 1","Hello !Wld...", "hello !wld...", &tests, &passed);

    TestBoolResult((FuncNoArgs) test_str_copy_hello, "str_copy 1", 1, &tests, &passed);
    TestBoolResult((FuncNoArgs) test_str_copy_hell, "str_copy 2", 1, &tests, &passed);
    TestBoolResult((Func) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);
    printf("%d/%d tests passed", passed, tests);
    return 0;
}