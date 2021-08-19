#include "dynamic_string.h"

size_t string_capacity(char *str) {
    if (str) {
        return *(((size_t*)str) - 1);
    } else {
        return 0;
    }
}

void string_set_capacity(char *str, size_t new_capacity) {
    if (str) {
        *(((size_t*)str) - 1) = new_capacity;
    }
}

size_t string_size(char *str) {
    if (str) {
       return *(((size_t*)str) - 2);
   } else {
       return 0;
   }
}

void string_set_size(char *str, size_t new_size) {
    if (str) {
        *(((size_t*)str) - 2) = new_size;
    }
}

int string_change_capacity(char **str, size_t new_capacity) {
    size_t* resized_str;
    size_t memory_needed = (2 * sizeof(size_t)) + (new_capacity + 1) * sizeof(char);
    if (*str) {
        size_t* ptr = ((size_t*)(*str)) - 2;
        resized_str = realloc(ptr, memory_needed);
    } else {
        resized_str = malloc(memory_needed);
    }

    if (!resized_str) return -1;

    *str = (char*)(resized_str + 2);
    string_set_capacity(*str, new_capacity);

    return 0;
}

void append_char(char **str, char c) {
    size_t capacity = string_capacity(*str);
    size_t size = string_size(*str);

    if (capacity == size) {
       if (capacity) {
           string_change_capacity(str, capacity * 2);
       } else {
           string_change_capacity(str, 1);
       }
    }
   (*str)[size] = c;
   (*str)[size + 1] = '\0';
   string_set_size(*str, size + 1);
}

void append_string(char **str, const char *string) {
    size_t str_size = string_size(*str);
    size_t to_append_size = strlen(string);
    size_t capacity = string_capacity(*str);

    if (capacity <= str_size + to_append_size) {
        if (!capacity) capacity = 1;
        while (capacity < str_size + to_append_size) {
            capacity = capacity * 2;
        }
        string_change_capacity(str, capacity);
   }

   for (int i = 0; i < to_append_size; i++) {
       (*str)[i + str_size] = string[i];
   }
   (*str)[str_size + to_append_size] = '\0';

   string_set_size(*str, str_size + to_append_size);
}

int erase_string_from_to(char **str, int begin, int end) {
   size_t size = string_size(*str);
   size_t capacity = string_capacity(*str);

   if (begin < 0 || end > size || begin > end) {
       return -1;
   }

   else {
       int to_eliminate = end - begin + 1;

       for (int i = 0; i < size - to_eliminate; i++) {
           (*str)[i + begin] = (*str)[i + end + 1];
       }

       if (size - to_eliminate <= capacity / 2) {
           while (size - to_eliminate < capacity) {
               if (capacity / 2 < size - to_eliminate) {
                   break;
               }
               capacity = capacity / 2;
           }
           string_change_capacity(str, capacity);
       }

       (*str)[size - to_eliminate] = '\0';
       string_set_size (*str, size - to_eliminate);
   }

   return 0;

}

bool string_equal_with_cons(char *str, int from, int to, const char *to_compare) {
    if (to - from + 1 <= strlen(to_compare) && (to + 1 <= string_size (str))) {
        int i = 0;
        while (from + i <= to) {
            if (str[from + i] != to_compare[i]) {
                return false;
            }
            i++;
        }
        return true;

    } else {
       printf("Error while comparing string with constant.\n");
       return false;
    }
}


void delete_string(char **str) {
    if (*str) {
        size_t* ptr = ((size_t*)(*str)) - 2;
        free(ptr);
        *str = NULL;
    }
}
