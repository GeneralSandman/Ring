
package main

import {
	fmt;
	debug;
}

@main
function main() {
    

    var int int_value;
    var int count;


    fmt::println_string("[test case 1]");

    for(int_value = 0; int_value < 10; ++int_value) {
        fmt::println_int(int_value);
    }



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 10);
    debug::debug_assert(int_value == 10);
    fmt::println_string("finish for====");




    // ------------------

    fmt::println_string("\n[test case 2]");

    count = 0;

    for(int_value = 0; int_value < 10; ++int_value) {
        if(int_value > 5) {
            continue;
        }
        count++;
        fmt::println_int(int_value);
    }



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 10);
    debug::debug_assert(int_value == 10);

    fmt::println_int(count);
    debug::debug_assert(count == 6);

    fmt::println_string("finish for====");



    // ------------------

    fmt::println_string("\n[test case 3]");

    count = 0;
    for(int_value = 0; int_value < 10; ++int_value) {
        if(int_value > 5) {
            break;
            continue;
        }
        count++;
        fmt::println_int(int_value);
    }



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 6);
    debug::debug_assert(int_value == 6);

    fmt::println_int(count);
    debug::debug_assert(count == 6);

    fmt::println_string("finish for====");

}
