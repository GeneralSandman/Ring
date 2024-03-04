#include "ring.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>


#define STRING_LITERAL_CAPACITY (1024)

static char*        string_literal_buffer          = nullptr;
static unsigned int string_literal_buffer_size     = 0;
static unsigned int string_literal_buffer_capacity = 0;


// new_ring_string
Ring_String* new_ring_string() {
    Ring_String* string = (Ring_String*)mem_alloc(NULL_MEM_POOL, sizeof(Ring_String));

    string->data        = (char*)mem_alloc(NULL_MEM_POOL, STRING_LITERAL_CAPACITY * sizeof(char));
    string->length      = 0;
    string->capacity    = STRING_LITERAL_CAPACITY;
    return string;
}

void reset_ring_string(Ring_String* string) {
    string->length = 0;
}

void ring_string_add_char(Ring_String* string, char ch) {
    if (string->length == string->capacity) {
        unsigned int old_alloc_size = string->capacity * sizeof(char);
        string->capacity += STRING_LITERAL_CAPACITY;
        unsigned int new_alloc_size = string->capacity * sizeof(char);

        string->data                = (char*)mem_realloc(NULL_MEM_POOL, string->data, old_alloc_size, new_alloc_size);
    }
    string->data[string->length] = ch;
    string->length++;
}

char* get_ring_string(Ring_String* string) {
    char* new_str;

    new_str = (char*)mem_alloc(NULL_MEM_POOL, string->length + 1);
    memcpy(new_str, string->data, string->length);
    new_str[string->length] = '\0';
    return new_str;
}


// ------------------------------


void init_string_literal_buffer() {
    string_literal_buffer = (char*)mem_alloc(NULL_MEM_POOL, STRING_LITERAL_CAPACITY * sizeof(char));
    if (string_literal_buffer == nullptr) {
        printf("[ERROR] alloc space error\n");
    }
    string_literal_buffer_size     = 0;
    string_literal_buffer_capacity = STRING_LITERAL_CAPACITY;
}

void reset_string_literal_buffer() {
    string_literal_buffer_size = 0;
}

void string_literal_add_char(char ch) {
    if (string_literal_buffer_size == string_literal_buffer_capacity) {
        unsigned int old_alloc_size = string_literal_buffer_capacity * sizeof(char);
        string_literal_buffer_capacity += STRING_LITERAL_CAPACITY;
        unsigned int new_alloc_size = string_literal_buffer_capacity * sizeof(char);

        string_literal_buffer       = (char*)mem_realloc(NULL_MEM_POOL, string_literal_buffer, old_alloc_size, new_alloc_size);
        if (string_literal_buffer == nullptr) {
            printf("[ERROR] mem_realloc error\n");
        }
    }
    string_literal_buffer[string_literal_buffer_size] = ch;
    string_literal_buffer_size++;
}

char* get_string_literal() {
    char* new_str;

    new_str = (char*)mem_alloc(NULL_MEM_POOL, string_literal_buffer_size + 1);
    if (new_str == nullptr) {
        printf("[ERROR] alloc space error\n");
    }
    memcpy(new_str, string_literal_buffer, string_literal_buffer_size);
    new_str[string_literal_buffer_size] = '\0';
    return new_str;
}
