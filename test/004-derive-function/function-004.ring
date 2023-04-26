
package main

import {
	fmt;
	debug;
}

global {
    var int int_value_global;
}



function func_use_local_variable_hidden_global() {
    var int int_value_global;
    int_value_global = 234;
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::debug_assert(int_value_global == 234);
    debug::debug_assert(int_value_global == 234);
    debug::debug_assert(int_value_global == 234);
    debug::debug_assert(int_value_global == 234);
}


// --------------

@main
function main() {

    int_value_global = 1;
    fmt::println_int(int_value_global);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    fmt::println_string("");
    
    func_use_local_variable_hidden_global();
    fmt::println_string("");
    
    fmt::println_int(int_value_global);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    debug::debug_assert(int_value_global == 1);
    fmt::println_string("");

}