//
// Created by robin.salihaxelsson on 2023-05-22.
//

#ifndef C_STRINGS_STRINGS_R_H
#define C_STRINGS_STRINGS_R_H

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;
};

struct document {
    struct paragraph* data;
    int paragraph_count;
};
int count_tokens(const char* text, const char* delimiters);
struct document get_document_struct(const char* text);
struct sentence get_sentence_struct(const char* text);
struct word get_word_struct(const char* chars);
struct paragraph get_paragraph_struct(const char* text);

int str_length(char* string);

int str_word_count(char* text);

int str_paragraph_count(char* text);

int str_sentence_count(char* text);

char* str_to_upper(char* string);

char* str_to_lower(char* string);

int char_is_delimiter(char character, char* delimiters);

int str_split_count(char* text, char* delimiters);

char** str_splitr(char* text, char* delimiters, char terminator);

char* string_join(char **strings, int len, char join_char);

int count_distinct_char(const char* str);

char**** get_document(char* text);

char*** get_sentences(char* text);

void free_document(char**** document);

void free_2dArr(char** words);

char* str_trim(char* source, char* characters);

char* str_left_trim(char* source, char* characters);

char* str_right_trim(char* source, char* characters);

void str_to_lower_in_place(char* string);

int lexicographic_sort(const char* a, const char* b);

int lexicographic_sort_reverse(const char* a, const char* b);

int sort_by_length(const char* a, const char* b);

int sort_by_number_of_distinct_characters(const char* a, const char* b);

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b));

char** doc_get_words(char* text);

char** doc_get_paragraphs(char* text);

int str_equal(char* strA, char* strB);

void str_copy(char* source, char* target);

void str_reverse(char* string, char* reverse);

#endif //C_STRINGS_STRINGS_R_H
