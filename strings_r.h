//
// Created by robin.salihaxelsson on 2023-05-22.
//

#ifndef C_STRINGS_STRINGS_R_H
#define C_STRINGS_STRINGS_R_H

int str_count(const char* string);

int str_word_count(const char* text);

char* str_to_upper(const char* string);

char* str_to_lower_copy(const char* string);

void str_to_lower_in_place(char* string);

int str_equal(char* strA, char* strB);

void str_copy(char* source, char* target);

void str_reverse(char* string, char* reverse);

#endif //C_STRINGS_STRINGS_R_H
