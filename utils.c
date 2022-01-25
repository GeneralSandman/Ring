#include <stdio.h>
#include "ring.h"

// 编译错误
void print_debug_info_with_red(const char *message) {
    printf("\033[31m%s\033[0m\n", message);
}

// 标示错误的地址
void print_debug_info_with_green(const char *message) {
    printf("\033[32m%s\033[0m\n", message);
}

void print_debug_info_with_yellow(const char *message) {
    printf("\033[33m%s\033[0m\n", message);
}

void print_debug_info_with_blue(const char *message) {
    printf("\033[34m%s\033[0m\n", message);
}

// 编译告警
void print_debug_info_with_purple(const char *message) {
    printf("\033[35m%s\033[0m\n", message);
}
