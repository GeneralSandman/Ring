#include "ring.h"
#include <stdio.h>
#include <string>

std::string a =
    "\033[0;31m*General Ring-Language Gramnmer Manual*\033[0m\n"
    "\n"

    "\033[0;33m+Name:\033[0m\n"
    "    Ring Quick Start HelloWorld\n"
    "\n"

    "\033[0;33m+DESCRIPTION:\033[0m\n"
    "    This program is a simple content of Ring-Language.\n"
    "\n"

    "\033[0;33m+USAGE:\033[0m\n"
    "    var bool bool_value;\n"
    "    var int int_value;\n"
    "    var float float_value;\n"
    "    var string string_value;\n"
    "\n"

    "\033[0;33m+Notice:\033[0m\n"
    "\n";


void ring_give_man_help(char* keyword) {
    printf("%s\n", a.c_str());
}
