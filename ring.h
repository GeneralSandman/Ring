#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

void init_string_literal_buffer();
void reset_string_literal_buffer();
void string_literal_add_char(char ch);
char *get_string_literal();

#endif