#include <stdio.h>
#include <malloc.h>
#include "../src/strings_r.h"

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

void test_int_equal(int expected, int result, char* name, int* tests, int* passed){
    (*tests)++;
    if(expected == result){
        (*passed)++;
    }
    else{
        printf("Fail: %s, expected: %d, result: %d\n", name, expected, result);
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

void Test_get_struct(int* tests, int* passed){
    struct word w1= get_word_struct("Hello");
    test_str_equal("Hello", w1.data, "word struct", tests, passed);

    struct sentence s1 = get_sentence_struct("Hello Earth");
    (*tests)++;
    if(s1.word_count == 2) (*passed)++;
    else printf("word count s1 failed");

    test_str_equal("Hello", s1.data[0].data, "sentence struct 1", tests, passed);
    test_str_equal("Earth", s1.data[1].data, "sentence struct 2", tests, passed);

    struct paragraph p1 = get_paragraph_struct("Hola Mujeres. Que pasa?");
    test_str_equal("Hola", p1.data[0].data[0].data, "paragraph struct 1", tests, passed);
    test_str_equal("Mujeres", p1.data[0].data[1].data, "paragraph struct 1", tests, passed);
    test_str_equal("Que", p1.data[1].data[0].data, "paragraph struct 2", tests, passed);
    test_str_equal("pasa?", p1.data[1].data[1].data, "paragraph struct 2", tests, passed);

    struct document d1 = get_document_struct("Welcome baby. This is great\nYou are back. Yes");
    test_str_equal("Welcome", d1.data[0].data[0].data[0].data, "document struct 1", tests, passed);

    struct document d2 = get_document_struct("Hello world");
    test_str_equal("Hello", d2.data[0].data[0].data[0].data, "document struct 2 hello", tests, passed);
}

void Test_token_count(int* tests, int* passed){
    int count2 = count_tokens("1\n6", "\n");
    (*tests)++;
    if(count2 == 2) (*passed)++;
    else printf("count tokens failed expected 2\n");

    int count1 = count_tokens("1.2.3.4.5.6", ".");
    (*tests)++;
    if(count1 == 6) (*passed)++;
    else printf("count tokens failed expected 6\n");
}

void Test_string_sort(int *tests, int *passed){
    char **input = str_splitr("wkue qoi sbv fekls", " ", '\0');

    string_sort(input, 4, lexicographic_sort);
    test_str_equal("fekls", input[0], "fekls string_sort lex", tests, passed);
    test_str_equal("qoi", input[1], "qoi string_sort lex", tests, passed);
    test_str_equal("sbv", input[2], "sbv string_sort lex", tests, passed);
    test_str_equal("wkue", input[3], "wkue string_sort lex", tests, passed);

    string_sort(input, 4, lexicographic_sort_reverse);
    test_str_equal("wkue", input[0], "string_sort reverse", tests, passed);
    test_str_equal("sbv", input[1], "string_sort reverse", tests, passed);
    test_str_equal("qoi", input[2], "string_sort reverse", tests, passed);
    test_str_equal("fekls", input[3], "string_sort reverse", tests, passed);

    string_sort(input, 4, sort_by_length);
    test_str_equal("qoi", input[0], "qoi string_sort length", tests, passed);
    test_str_equal("sbv", input[1], "sbv string_sort length", tests, passed);
    test_str_equal("wkue", input[2], "wkue string_sort length", tests, passed);
    test_str_equal("fekls", input[3], "fekls string_sort length", tests, passed);

    char** arr = str_splitr("abbbbbc aa abcd ab", " ", '\0');
    string_sort(arr, 4, sort_by_number_of_distinct_characters);
    test_str_equal("aa", arr[0], "aa string_sort distinct length", tests, passed);
    test_str_equal("ab", arr[1], "ab string_sort distinct length", tests, passed);
    test_str_equal("abbbbbc", arr[2], "abbbbbc string_sort distinct length", tests, passed);
    test_str_equal("abcd", arr[3], "abcd string_sort distinct length", tests, passed);

    char** arr2 = str_splitr("aab aabbc aabb aa", " ", '\0');
    string_sort(arr2, 4, lexicographic_sort);
    test_str_equal("aa", arr2[0], "aa sort lexicographic_sort", tests, passed);
    test_str_equal("aab", arr2[1], "aa sort lexicographic_sort", tests, passed);
    test_str_equal("aabb", arr2[2], "aa sort lexicographic_sort", tests, passed);
    test_str_equal("aabbc", arr2[3], "aa sort lexicographic_sort", tests, passed);

    char** arr3 = str_splitr("ibahqaceux prmv ovsylj ta eovfkgikn mrhgpexi s gqrhdd wfy uwhgessrv kcm gl zgjhycobhl njzjhi lchexnrzbs mch n srftz umbtxle ygvfe wfnonbs wfnqxsmwk k ajwgxxou u yatmpuf qmbhl vjfbvq epjboyvq bouuckp yhyzqjsltz opqtgauu smstanofz qxmowfyq t fhgwcp zjyrysk hafgh f kbbkt dk lrvn", " ", '\0');

    string_sort(arr3, 42, lexicographic_sort);
    char *join_lex_sort = string_join(arr3, 42, ' ');
    test_str_equal("ajwgxxou bouuckp dk eovfkgikn epjboyvq f fhgwcp gl gqrhdd hafgh ibahqaceux k kbbkt kcm lchexnrzbs lrvn mch mrhgpexi n njzjhi opqtgauu ovsylj prmv qmbhl qxmowfyq s smstanofz srftz t ta u umbtxle uwhgessrv vjfbvq wfnonbs wfnqxsmwk wfy yatmpuf ygvfe yhyzqjsltz zgjhycobhl zjyrysk", join_lex_sort, "join lex sort", tests, passed);

    string_sort(arr3, 42, lexicographic_sort_reverse);
    char *join_lex_sort_reverse = string_join(arr3, 42, ' ');
    test_str_equal("zjyrysk zgjhycobhl yhyzqjsltz ygvfe yatmpuf wfy wfnqxsmwk wfnonbs vjfbvq uwhgessrv umbtxle u ta t srftz smstanofz s qxmowfyq qmbhl prmv ovsylj opqtgauu njzjhi n mrhgpexi mch lrvn lchexnrzbs kcm kbbkt k ibahqaceux hafgh gqrhdd gl fhgwcp f epjboyvq eovfkgikn dk bouuckp ajwgxxou", join_lex_sort_reverse, "join lex sort reverse", tests, passed);

    string_sort(arr3, 42, sort_by_length);
    char *join_lex_sort_length = string_join(arr3, 42, ' ');
    test_str_equal("f k n s t u dk gl ta kcm mch wfy lrvn prmv hafgh kbbkt qmbhl srftz ygvfe fhgwcp gqrhdd njzjhi ovsylj vjfbvq bouuckp umbtxle wfnonbs yatmpuf zjyrysk ajwgxxou epjboyvq mrhgpexi opqtgauu qxmowfyq eovfkgikn smstanofz uwhgessrv wfnqxsmwk ibahqaceux lchexnrzbs yhyzqjsltz zgjhycobhl", join_lex_sort_length, "join lex sort length", tests, passed);

    string_sort(arr3, 42, sort_by_number_of_distinct_characters);
    char *join_lex_sort_distinct_length = string_join(arr3, 42, ' ');
    test_str_equal("f k n s t u dk gl ta kbbkt kcm mch wfy hafgh lrvn prmv gqrhdd njzjhi qmbhl srftz vjfbvq ygvfe bouuckp fhgwcp ovsylj wfnonbs zjyrysk ajwgxxou opqtgauu qxmowfyq umbtxle yatmpuf eovfkgikn epjboyvq mrhgpexi smstanofz uwhgessrv wfnqxsmwk yhyzqjsltz ibahqaceux zgjhycobhl lchexnrzbs", join_lex_sort_distinct_length, "join lex sort length", tests, passed);

    // char** arr4 = str_splitr("hjzzwdq upsovufynjgyndaslodyexwlgxmfbdtxunmphtq ewwrcyknmnnsmmetjsamvvkriyhrrznyvjpxjznvpcobouw mwmkrydbwmsqlhohsdgbftxwylzohyovudf bjryxmojteqmhypmumkszkgiiveea ubwmzuypdttvhd xrnl hnmovwlbalnxmjlodjfiebdmezlvoyzwlnkjjvkmi jujukofsxltazxbkuqjumw yhtvshdtsz okrvcqgxsgwusqkbmyawwhrrbyuvstz fsbjihgbpcvivhljfnfdvyuyyqtqlvwtnzcwjlx puikbwuijbl affaxariv bjpghyreygahrbdnjm utqbaryak wzkhoqomhulpuuivxvglmcgcdgvdhflffvmvnckwwxm runqsvbexiicqghxlsesqqqds cqxoiqkxgcshgrrrvixchkxmf evszvupu akvxqxqzgjtxfdwjmggylvfgo divztvjqtbnldtuwsbbolnx", " ", '\0');

//    string_sort(arr4, 22, sort_by_number_of_distinct_characters);
//    char *join_arr4_lex_sort_distinct_length = string_join(arr4, 22, ' ');
//    test_str_equal("xrnl affaxariv evszvupu hjzzwdq yhtvshdtsz puikbwuijbl utqbaryak ubwmzuypdttvhd bjpghyreygahrbdnjm cqxoiqkxgcshgrrrvixchkxmf divztvjqtbnldtuwsbbolnx jujukofsxltazxbkuqjumw runqsvbexiicqghxlsesqqqds akvxqxqzgjtxfdwjmggylvfgo hnmovwlbalnxmjlodjfiebdmezlvoyzwlnkjjvkmi okrvcqgxsgwusqkbmyawwhrrbyuvstz wzkhoqomhulpuuivxvglmcgcdgvdhflffvmvnckwwxm mwmkrydbwmsqlhohsdgbftxwylzohyovudf bjryxmojteqmhypmumkszkgiiveea fsbjihgbpcvivhljfnfdvyuyyqtqlvwtnzcwjlx ewwrcyknmnnsmmetjsamvvkriyhrrznyvjpxjznvpcobouw upsovufynjgyndaslodyexwlgxmfbdtxunmphtq", join_arr4_lex_sort_distinct_length, "join lex sort length", tests, passed);
}

void Test_str_join(int *tests, int *passed){
    char **text_array = str_splitr("Hello World, mother fucker", " ", '\0');
    char *join = string_join(text_array, 4, ' ');
    test_str_equal("Hello World, mother fucker", join, "string join", tests, passed);
}

void Test_count_unique_char(int *tests, int *passed){
    int distinct1 = count_distinct_char("njzjhi");
    test_int_equal(5, distinct1, "count disinct", tests, passed);

    int distinct_z = count_distinct_char("z");
    test_int_equal(1, distinct_z, "count disinct", tests, passed);

    int distinct_y = count_distinct_char("y");
    test_int_equal(1, distinct_y, "count disinct", tests, passed);
}

int main() {
    int tests = 0;
    int passed = 0;
    Test_count_unique_char(&tests, &passed);
    Test_str_join(&tests, &passed);
    Test_string_sort(&tests, &passed);
    Test_token_count(&tests, &passed);
    Test_get_struct(&tests, &passed);
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

    TestStrResult((FuncStr)str_to_upper, "to upper 1","HELLO WORLD", "HELLO WORLD", &tests, &passed);
    TestStrResult((FuncStr)str_to_upper, "to upper 2","hello world", "HELLO WORLD", &tests, &passed);
    TestStrResult((FuncStr)str_to_upper, "to upper 3","hello !Wld...", "HELLO !WLD...", &tests, &passed);
    TestStrResult((FuncStr) str_to_lower, "to lower 1", "Hello !Wld...", "hello !wld...", &tests, &passed);

    TestBoolResult((FuncNoArgs) test_str_copy_hello, "str_copy 1", 1, &tests, &passed);
    TestBoolResult((FuncNoArgs) test_str_copy_hell, "str_copy 2", 1, &tests, &passed);
    TestBoolResult((FuncNoArgs) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);

    TestBoolResult((FuncNoArgs) test_str_reverse_Abc, "reverse 1", 1, &tests, &passed);

    Test_doc_get_words("get words", &tests, &passed);
    Test_doc_get_paragraphs("get paragraphs", &tests, &passed);
    Test_doc_contains("contains 1", &tests, &passed);
    Test_get_sentence(&tests, &passed);
    Test_doc_structure(&tests, &passed);
    Test_str_trim(&tests, &passed);
    Test_str_left_trim(&tests, &passed);
    Test_str_right_trim(&tests, &passed);
    printf("%d/%d tests passed", passed, tests);
    return 0;
}
