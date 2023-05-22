#include <stdio.h>
#include "strings_r.h"

typedef int (*FuncInt)(void*);
typedef char* (*FuncStr)(void*);
typedef int (*FuncNoArgs)();

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

    int result = func();
    if(expectedBool == result){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expectedBool: %d, result: %d\n", testName, expectedBool, result);
    }
}

void TestIntResult(FuncInt func, char* testName, void* data, int expected, int* tests, int* passed){
    (*tests)++;

    int result = func(data);
    if(expected == result){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expected: %d, result: %d\n", testName, expected, result);
    }
}

void TestStrResult(FuncStr func, char* testName, void* data, char* expected, int* tests, int* passed){
    (*tests)++;

    char* result = func(data);
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

    TestIntResult((FuncInt) str_word_count, "count_words__3_words__3", "Hello counting words", 3, &tests, &passed);
    TestIntResult((FuncInt) str_word_count, "count_words__5_words_newline__5", "Hello world!\nYou are great", 5, &tests,
                  &passed);
    TestIntResult((FuncInt) str_word_count, "count_words__0_words__0", "", 0, &tests, &passed);
    TestIntResult((FuncInt) str_count, "count_chars__words__5", "abcde", 5, &tests, &passed);
    TestIntResult((FuncInt) str_count, "count_chars__empty__5", "", 0, &tests, &passed);

    TestStrResult((FuncStr)str_to_upper, "to upper 1","HELLO WORLD", "HELLO WORLD", &tests, &passed);
    TestStrResult((FuncStr)str_to_upper, "to upper 2","hello world", "HELLO WORLD", &tests, &passed);
    TestStrResult((FuncStr)str_to_upper, "to upper 3","hello !Wld...", "HELLO !WLD...", &tests, &passed);
    TestStrResult((FuncStr)str_to_lower_copy, "to lower 1","Hello !Wld...", "hello !wld...", &tests, &passed);

    TestBoolResult((FuncNoArgs) test_str_copy_hello, "str_copy 1", 1, &tests, &passed);
    TestBoolResult((FuncNoArgs) test_str_copy_hell, "str_copy 2", 1, &tests, &passed);
    TestBoolResult((FuncNoArgs) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);
    printf("%d/%d tests passed", passed, tests);
    return 0;
}