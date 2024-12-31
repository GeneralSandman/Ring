
package main

import {
	fmt;
	debug;
}

global {
    var int int_value_global;
}

fn func_use_local_variable() {
    var int int_value_local;
    int_value_local = 123;
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    fmt::println_int(int_value_local);
    debug::assert(int_value_local == 123);
    debug::assert(int_value_local == 123);
    debug::assert(int_value_local == 123);
    debug::assert(int_value_local == 123);
}

// --------------

@main
fn main() {

    int_value_global = 2;
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    fmt::println_string("");

    func_use_local_variable();
    fmt::println_string("");

    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    fmt::println_int(int_value_global);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    debug::assert(int_value_global == 2);
    fmt::println_string("");


}