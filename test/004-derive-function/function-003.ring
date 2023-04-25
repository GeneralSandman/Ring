
package main

import {
	fmt;
	debug;
}


var int int_value_global;




function func_use_global_variable() {
    int_value_global = 222;
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::debug_assert(int_value_global == 222);
    debug::debug_assert(int_value_global == 222);
    debug::debug_assert(int_value_global == 222);
    debug::debug_assert(int_value_global == 222);
}


// --------------

@main
function main() {

int_value_global = 1;
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
debug::debug_assert(int_value_global == 1);
debug::debug_assert(int_value_global == 1);
debug::debug_assert(int_value_global == 1);
debug::debug_assert(int_value_global == 1);
fmt::println_string("");

func_use_global_variable();
fmt::println_string("");

fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
debug::debug_assert(int_value_global == 222);
debug::debug_assert(int_value_global == 222);
debug::debug_assert(int_value_global == 222);
debug::debug_assert(int_value_global == 222);
fmt::println_string("");

}