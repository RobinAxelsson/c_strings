#include <stdio.h>
#include <malloc.h>
#include "strings_r.h"

typedef int (*FuncInt)(void*);
typedef char* (*FuncStr)(void*);
typedef int (*FuncNoArgs)();

void assert_true(int result, char* name, int* tests, int* passed){
    (*tests)++;
    if(result){
        (*passed)++;
    }
    else{
        printf("Fail: %s\n", name);
    }
}

void test_str_equal(char* expected, char* result, char* name, int* tests, int* passed){
    (*tests)++;
    if(str_equal(expected, result)){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expected: %s, result: %s\n", name, expected, result);
    }
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

    free(result);
    result = NULL;
}

void Test_doc_get_words(char* testName, int* tests, int* passed){
    (*tests)++;

    char** result = doc_get_words("Hello world my friends");

    char expected[4][10];
    str_copy( "Hello", expected[0]);
    str_copy("world", expected[1]);
    str_copy("my", expected[2]);
    str_copy("friends", expected[3]);

    int failed = 0;
    for (int i = 0; i < 4; ++i) {
        if(!str_equal(result[i], expected[i])) failed = 1;
    }
    if(failed){
        printf("Fail: %s\n", testName);
    }
    else{
        (*passed)++;
    }

    free_2dArr(result);
    result = NULL;
}

void Test_doc_get_paragraphs(char* testName, int* tests, int* passed){
    (*tests)++;

    char hello[] = "Hello\nworld";
    char** result = doc_get_paragraphs(hello);

    if(str_equal(result[0], "Hello") && str_equal(result[1], "world")){
        (*passed)++;
    }
    else{
        printf("Fail: %s\n", testName);
    }

    free_2dArr(result);
    result = NULL;
}

void Test_doc_contains(char* testName, int* tests, int* passed){
    (*tests)++;

    char character = '!';
    char string[] = ".!.";
    int result = char_is_delimiter(character, string);

    char character1 = '!';
    char string1[] = "...";
    int result1 = char_is_delimiter(character1, string1);

    if(result && !result1){
        (*passed)++;
    }
    else{
        printf("Fail: %s\n", testName);
    }
}

void Test_doc_structure(int* tests, int* passed){

char**** nullDocument = get_document(NULL);
assert_true(nullDocument == NULL, "doc: NULL text", tests, passed);

char nullArray[1];
nullArray[0] = '\0';
    nullDocument = get_document(nullArray);

assert_true(nullDocument == NULL, "doc: NULL text", tests, passed);
free_document(nullDocument);

char**** document = get_document("Hello World. Hey.\nnewline");
assert_true(document != NULL, "doc ptr", tests, passed);
char*** paragraph0 = document[0];
assert_true(paragraph0 != NULL, "text expect not null", tests, passed);
char** sentence0 = paragraph0[0];
assert_true(sentence0 != NULL, "text expect not null", tests, passed);

char* word0 = sentence0[0];
test_str_equal("Hello", word0, "Test document for Hello", tests, passed);
char* word1 = sentence0[1];
test_str_equal("World", word1, "Test document World", tests, passed);

char** sentence1 = paragraph0[1];
test_str_equal("Hey", sentence1[0], "Test document for Hey", tests, passed);

char* word100 = document[1][0][0];
test_str_equal("newline", word100, "test for newline", tests, passed);

free_document(document);

char**** document1 = get_document("Next");

test_str_equal("Next", document1[0][0][0], "test for not hardcoded", tests, passed);
free_document(document1);
}

void Test_get_sentence(int* tests, int* passed){

    char* text = "Hello world! Hey bro!";
    char*** result = get_sentences(text);
    char** sentence0 = result[0];
    char** sentence1 = result[1];
    char* word0 = sentence0[0];
    char* word1 = sentence0[1];
    char* word2 = sentence1[0];
    char* word3 = sentence1[1];

    test_str_equal("Hello", word0, "get sentences", tests, passed);
    test_str_equal("world", word1, "get sentences", tests, passed);
    test_str_equal("Hey", word2, "get sentences", tests, passed);
    test_str_equal("bro", word3, "get sentences", tests, passed);
}
void Test_str_right_trim(int* tests, int* passed) {
    test_str_equal("A", str_right_trim("A", "."), "right trim", tests, passed);
    test_str_equal("A", str_right_trim("A.", "."), "right trim", tests, passed);
    test_str_equal("Aa", str_right_trim("Aa.", "."), "right trim", tests, passed);
    test_str_equal(NULL, str_right_trim(NULL, "."), "trim", tests, passed);
    test_str_equal("a.g", str_right_trim("a.g.", "."), "trim", tests, passed);
    test_str_equal(".....a.g", str_right_trim(".....a.g....", "."), "trim", tests, passed);
    test_str_equal("A", str_right_trim("A_", "_"), "trim", tests, passed);
    test_str_equal("A", str_right_trim("A", NULL), "trim", tests, passed);
    test_str_equal("", str_right_trim(".", "."), "trim", tests, passed);
    test_str_equal("A", str_right_trim("A._", "_."), "trim", tests, passed);
    test_str_equal("!.-_ \nA", str_right_trim("!.-_ \nA!.-_ \nb\n", "_.-!\nb "), "trim", tests, passed);
    char nullArray[1];
    nullArray[0] = '\0';
    test_str_equal(NULL, str_right_trim(nullArray, "."), "trim", tests, passed);
    test_str_equal("A", str_right_trim("A", nullArray), "trim", tests, passed);
}

void Test_str_left_trim(int* tests, int* passed){
    test_str_equal("A", str_left_trim("A", "."), "trim", tests, passed);
    test_str_equal("A", str_left_trim(".A", "."), "trim", tests, passed);
    test_str_equal("B", str_left_trim(".B", "."), "trim", tests, passed);
    test_str_equal("Ba", str_left_trim(".Ba", "."), "trim", tests, passed);
    test_str_equal(NULL, str_left_trim(NULL, "."), "trim", tests, passed);
    test_str_equal("a.g", str_left_trim(".a.g", "."), "trim", tests, passed);
    test_str_equal("a.g....", str_left_trim(".....a.g....", "."), "trim", tests, passed);
    test_str_equal("A", str_left_trim("_A", "_"), "trim", tests, passed);
    test_str_equal("A", str_left_trim("A", NULL), "trim", tests, passed);
    test_str_equal("", str_left_trim(".", "."), "trim", tests, passed);
    test_str_equal("A", str_left_trim("_.A", "_."), "trim", tests, passed);
    test_str_equal("A!.-_ \nb\n", str_left_trim("!.-_ \nA!.-_ \nb\n", "_.-!\n "), "trim", tests, passed);

    char nullArray[1];
    nullArray[0] = '\0';
    test_str_equal(NULL, str_left_trim(nullArray, "."), "trim", tests, passed);
    test_str_equal("A", str_left_trim("A", nullArray), "trim", tests, passed);
}

void Test_str_trim(int* tests, int* passed){
    char* hello = str_trim("...Hello!!", ".! ");
    char* my_bad = str_trim("..\n.my bad!!:, ", ".! \n:,");
    test_str_equal("Hello", hello, "trim", tests, passed);
    test_str_equal("my bad", my_bad, "trim", tests, passed);
}

int main() {
    int tests = 0;
    int passed = 0;

    TestIntResult((FuncInt) str_word_count, "count_words__3_words__3", "Hello counting words", 3, &tests, &passed);
    TestIntResult((FuncInt) str_word_count, "count_words__5_words_newline__5", "Hello world!\nYou are great", 5, &tests, &passed);
    TestIntResult((FuncInt) str_word_count, "count_words__5_words_extra_newline__5", "Hello world!\n\nYou are great", 5, &tests, &passed);
    TestIntResult((FuncInt) str_sentence_count, "count_sentence__", "Hello. world!\n\nYou are great?", 3, &tests, &passed);
    TestIntResult((FuncInt) str_sentence_count, "count_sentence__!!!!", "Hello. world!!!!!!!!!!!!!!!!!!\n\nYou are great?", 3, &tests, &passed);
    TestIntResult((FuncInt) str_paragraph_count, "count_para__4", "Hello!\nNew Para\nWhy\nGreat", 4, &tests, &passed);
    TestIntResult((FuncInt) str_paragraph_count, "count_para__4_extra_newline", "Hello!\nNew Para\n\nWhy\nGreat", 4, &tests, &passed);
    TestIntResult((FuncInt) str_paragraph_count, "count_para__4_extra_newline", "Hello\nworld", 2, &tests, &passed);
    TestIntResult((FuncInt) str_word_count, "count_words__0_words__0", "", 0, &tests, &passed);
    TestIntResult((FuncInt) str_length, "count_chars__words__5", "abcde", 5, &tests, &passed);
    TestIntResult((FuncInt) str_length, "count_chars__empty__5", "", 0, &tests, &passed);

//    TestStrResult((FuncStr)str_to_upper, "to upper 1","HELLO WORLD", "HELLO WORLD", &tests, &passed);
//    TestStrResult((FuncStr)str_to_upper, "to upper 2","hello world", "HELLO WORLD", &tests, &passed);
//    TestStrResult((FuncStr)str_to_upper, "to upper 3","hello !Wld...", "HELLO !WLD...", &tests, &passed);
//    TestStrResult((FuncStr) str_to_lower, "to lower 1", "Hello !Wld...", "hello !wld...", &tests, &passed);

//    TestBoolResult((FuncNoArgs) test_str_copy_hello, "str_copy 1", 1, &tests, &passed);
//    TestBoolResult((FuncNoArgs) test_str_copy_hell, "str_copy 2", 1, &tests, &passed);
//    TestBoolResult((FuncNoArgs) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);
//
//    TestBoolResult((FuncNoArgs) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);
//
//    Test_doc_get_words("get words", &tests, &passed);
//    Test_doc_get_paragraphs("get paragraphs", &tests, &passed);
//    Test_doc_contains("contains 1", &tests, &passed);
//    Test_get_sentence(&tests, &passed);
    Test_doc_structure(&tests, &passed);
//    Test_str_trim(&tests, &passed);
//    Test_str_left_trim(&tests, &passed);
//    Test_str_right_trim(&tests, &passed);
    printf("%d/%d tests passed", passed, tests);
    return 0;
}
