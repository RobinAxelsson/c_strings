//
// Created by robin.salihaxelsson on 2023-05-22.
//

#ifndef C_STRINGS_STRINGS_R_H
#define C_STRINGS_STRINGS_R_H

int str_length(char* string);

int str_word_count(char* text);

int str_paragraph_count(char* text);

int str_sentence_count(char* text);

char* str_to_upper(char* string);

char* str_to_lower(char* string);

int char_is_delimiter(char character, char* delimiters);

int str_split_count(char* text, char* delimiters);

char**** get_document(char* text);

char*** get_sentences(char* text);

void free_document(char**** document);

void free_2dArr(char** words);

char* str_trim(char* source, char* characters);

char* str_left_trim(char* source, char* characters);

char* str_right_trim(char* source, char* characters);

void str_to_lower_in_place(char* string);

char** doc_get_words(char* text);

char** doc_get_paragraphs(char* text);

int str_equal(char* strA, char* strB);

void str_copy(char* source, char* target);

void str_reverse(char* string, char* reverse);

#endif //C_STRINGS_STRINGS_R_H
