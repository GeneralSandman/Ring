
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

    do(int_value = 2){
        fmt::println_int(int_value);
    }for(int_value < 10; ++int_value);



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    debug::debug_assert(int_value == 10);
    fmt::println_string("finish for====");




    // ------------------

    fmt::println_string("\n[test case 2]");

    count = 0;

    do(int_value = 0) {
        if(int_value > 5) {
            continue;
        }
        count++;
        fmt::println_int(int_value);
    }for(int_value < 10; ++int_value);



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

    do(int_value = 0) {
        if(int_value % 2 == 0) {
            fmt::println_int(int_value);
        } else {
            continue;
        }
        count++;
    }for(int_value < 20; ++int_value);



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 20);
    debug::debug_assert(int_value == 20);

    fmt::println_int(count);
    debug::debug_assert(count == 11);

    fmt::println_string("finish for====");



    // ------------------

    fmt::println_string("\n[test case 4]");

    count = 0;

    do(int_value = 0) {
        if(int_value % 5 == 0) {
        } else {
            continue;
        }
        count++;
    }for(int_value < 100; ++int_value);



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 100);
    debug::debug_assert(int_value == 100);

    fmt::println_int(count);
    debug::debug_assert(count == 21);

    fmt::println_string("finish for====");



    // ------------------

    fmt::println_string("\n[test case 5]");

    count = 0;

    do(int_value = 0) {
        if(int_value % 5 == 0) {
            count = ++count;
        } else {
            continue;
        }
    }for(int_value < 100; ++int_value);



    fmt::println_string("finish for====");
    fmt::println_int(int_value);
    fmt::println_bool(int_value == 100);
    debug::debug_assert(int_value == 100);

    fmt::println_int(count);
    debug::debug_assert(count == 21);

    fmt::println_string("finish for====");


}