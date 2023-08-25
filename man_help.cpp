#include "ring.h"
#include <stdio.h>
#include <string.h>
#include <string>

std::string help_list =
    "Your can try those keyword:\n"
    "    \033[0;31m ring man var \033[0m         :variable definite\n"
    "    \033[0;31m ring man func \033[0m        :function definite\n"
    "    \033[0;31m ring man global_var \033[0m  :global variable definite\n"
    "    \033[0;31m ring man import \033[0m      :import package\n"
    "    \033[0;31m ring man --list \033[0m      :list all man keyword\n"
    "\n";

std::string variable_definite =
    "\033[0;31m General Ring-Language Gramnmer Manual \033[0m\n"
    "\n"

    "\033[0;33m+Name:\033[0m\n"
    "    variable\n"
    "\n"

    "\033[0;33m+Description:\033[0m\n"
    "    How to definite a variable.\n"
    "\n"

    "\033[0;33m+Gramnmer/Usage:\033[0m\n"
    "    var bool/int/double/string <identifier> [ =  initializer];\n"
    "\n"

    "\033[0;33m+Example:\033[0m\n"
    "    var bool bool_value;\n"
    "    var int int_value;\n"
    "    var double double_value;\n"
    "    var string string_value;\n"
    "\n"

    "\033[0;33m+Notice:\033[0m\n"
    "\n";

std::string function_definite =
    "\033[0;31m General Ring-Language Gramnmer Manual \033[0m\n"
    "\n"

    "\033[0;33m+Name:\033[0m\n"
    "    function\n"
    "\n"

    "\033[0;33m+Description:\033[0m\n"
    "    How to definite a function.\n"
    "\n"

    "\033[0;33m+Gramnmer/Usage:\033[0m\n"
    "   function <identifier> (parameter_list) -> (return_value_list) {\n"
    "       code_block;\n"
    "   }\n"
    "\n"

    "\033[0;33m+Example:\033[0m\n"
    "   function doit1() {\n"
    "       fmt::println_string(\"I'm function doit1, go go go!\");\n"
    "   }\n"
    "\n"

    "\033[0;33m+Notice:\033[0m\n"
    "\n";

std::string global_variable_definite =
    "\033[0;31m General Ring-Language Gramnmer Manual \033[0m\n"
    "\n"

    "\033[0;33m+Name:\033[0m\n"
    "    global variable\n"
    "\n"

    "\033[0;33m+Description:\033[0m\n"
    "    How to definite global variable.\n"
    "\n"

    "\033[0;33m+Gramnmer/Usage:\033[0m\n"
    "   global {\n"
    "       var bool/int/double/string <identifier>;\n"
    "   }\n"
    "\n"

    "\033[0;33m+Example:\033[0m\n"
    "   global {\n"
    "       var bool bool_value;\n"
    "       var int int_value;\n"
    "       var double double_value;\n"
    "       var string string_value;\n"
    "   }\n"
    "\n"

    "\033[0;33m+Notice:\033[0m\n"
    "\n";

std::string import =
    "\033[0;31m General Ring-Language Gramnmer Manual \033[0m\n"
    "\n"

    "\033[0;33m+Name:\033[0m\n"
    "    import package\n"
    "\n"

    "\033[0;33m+Description:\033[0m\n"
    "    How to import package in head of Ring source code file.\n"
    "\n"

    "\033[0;33m+Gramnmer/Usage:\033[0m\n"
    "   import {\n"
    "       <identifier>;\n"
    "   }\n"
    "\n"

    "\033[0;33m+Example:\033[0m\n"
    "   import {\n"
    "       fmt;\n"
    "       debug;\n"
    "   }\n"
    "\n"

    "\033[0;33m+Notice:\033[0m\n"
    "\n";

void ring_give_man_help(char* keyword) {
    std::string res = help_list;
    if (0 == strcmp(keyword, "var")) {
        res = variable_definite;
    } else if (0 == strcmp(keyword, "func")) {
        res = function_definite;
    } else if (0 == strcmp(keyword, "global_var")) {
        res = global_variable_definite;
    } else if (0 == strcmp(keyword, "import")) {
        res = import;
    } else if (0 == strcmp(keyword, "--list")) {
        res = help_list;
    }
    printf("%s", res.c_str());
}
