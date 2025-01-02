
package main

import {
	fmt;
	debug;
}


global {
    var int int_value_global;
}





fn func_use_global_variable() {
    int_value_global = 222;
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
}


// --------------


fn main() {

    int_value_global = 1;
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::assert(int_value_global == 1);
    debug::assert(int_value_global == 1);
    debug::assert(int_value_global == 1);
    debug::assert(int_value_global == 1);
    fmt::println_string("");

    func_use_global_variable();
    fmt::println_string("");

    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
    debug::assert(int_value_global == 222);
    fmt::println_string("");

}