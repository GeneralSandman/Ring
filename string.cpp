#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LITERAL_CAPACITY (1024)

static char* string_literal_buffer          = nullptr;
static int   string_literal_buffer_size     = 0;
static int   string_literal_buffer_capacity = 0;

Ring_String* new_ring_string() {
    Ring_String* string = (Ring_String*)malloc(sizeof(Ring_String));

    string->buffer   = (char*)malloc(STRING_LITERAL_CAPACITY);
    string->size     = 0;
    string->capacity = STRING_LITERAL_CAPACITY;
    return string;
}

void reset_ring_string(Ring_String* string) {
    string->size = 0;
}

void ring_string_add_char(Ring_String* string, char ch) {
    if (string->size == string->capacity) {
        string->capacity += STRING_LITERAL_CAPACITY;
        string->buffer = (char*)realloc(string->buffer, string->capacity);
    }
    string->buffer[string->size] = ch;
    string->size++;
}

char* get_ring_string(Ring_String* string) {
    char* new_str;

    new_str = (char*)malloc(string->size + 1);
    memcpy(new_str, string->buffer, string->size);
    new_str[string->size] = '\0';
    return new_str;
}

void init_string_literal_buffer() {
    string_literal_buffer = (char*)malloc(STRING_LITERAL_CAPACITY);
    if (string_literal_buffer == nullptr) {
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
        string_literal_buffer = (char*)realloc(string_literal_buffer, string_literal_buffer_capacity);
        if (string_literal_buffer == nullptr) {
            printf("[ERROR] realloc error\n");
        }
    }
    string_literal_buffer[string_literal_buffer_size] = ch;
    string_literal_buffer_size++;
}

char* get_string_literal() {
    char* new_str;

    new_str = (char*)malloc(string_literal_buffer_size + 1);
    if (new_str == nullptr) {
        printf("[ERROR] malloc error\n");
    }
    memcpy(new_str, string_literal_buffer, string_literal_buffer_size);
    new_str[string_literal_buffer_size] = '\0';
    return new_str;
}
