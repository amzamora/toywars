#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define String char*

size_t string_capacity(char *str);
void string_set_capacity(char *str, size_t new_capacity);
size_t string_size(char *str);
void string_set_size(char *str, size_t new_size);
int string_change_capacity(char **str, size_t new_capacity);
void append_char(char **str, char c);
void append_string(char **str, const char *string);
int erase_string_from_to(char **str, int begin, int end);
bool string_equal_with_cons(char *str, int from, int to, const char *to_compare);
void delete_string(char **str);


#endif
