#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LITERAL_CAPACITY (1024)

static char *string_literal_buffer          = NULL;
static int   string_literal_buffer_size     = 0;
static int   string_literal_buffer_capacity = 0;

void init_string_literal_buffer() {
    string_literal_buffer = malloc(STRING_LITERAL_CAPACITY);
    if (string_literal_buffer == NULL) {
        printf("[ERROR] malloc error\n");
    }
    string_literal_buffer_size     = 0;
    string_literal_buffer_capacity = STRING_LITERAL_CAPACITY;
}

void reset_string_literal_buffer() {
    string_literal_buffer_size = 0;
}

void string_literal_add_char(char ch) {
    if (string_literal_buffer_size == string_literal_buffer_capacity) {
        string_literal_buffer_capacity += STRING_LITERAL_CAPACITY;
        string_literal_buffer = realloc(string_literal_buffer, string_literal_buffer_capacity);
        if (string_literal_buffer == NULL) {
            printf("[ERROR] realloc error\n");
        }
    }
    string_literal_buffer[string_literal_buffer_size] = ch;
    string_literal_buffer_size++;
}

char *get_string_literal() {
    char *new_str;

    new_str = malloc(string_literal_buffer_size + 1);
    if (new_str == NULL) {
        printf("[ERROR] malloc error\n");
    }
    memcpy(new_str, string_literal_buffer, string_literal_buffer_size);
    new_str[string_literal_buffer_size] = '\0';
    return new_str;
}
