
package main

import {
	fmt;
	debug;
}


var int int_value_global;


function func_use_local_variable() {
    var int int_value_local;
    int_value_local = 123;
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    debug::debug_assert(int_value_local == 123);
    debug::debug_assert(int_value_local == 123);
    debug::debug_assert(int_value_local == 123);
    debug::debug_assert(int_value_local == 123);
}

// --------------

@main
function main() {

int_value_global = 2;
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
fmt::println_string("");

func_use_local_variable();
fmt::println_string("");

fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
fmt::println_int(int_value_global);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
debug::debug_assert(int_value_global == 2);
fmt::println_string("");


}