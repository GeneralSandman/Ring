
package main

import {
	fmt;
	debug;
}

@main
function main() {

    var int int_value_1;
    var int int_value_2;
    var int count;

    // -----------
    fmt::println_string("[Test Case 1]");

    count = 0;

    do(int_value_1 = 0) {

        do(int_value_2 = 0) {
            count++;
        }for(int_value_2<5; int_value_2++);

    }for(int_value_1<10; int_value_1++);

    fmt::println_string("finish for====");
    debug::debug_assert(count == 11 * 6);
    fmt::println_int(count);
    debug::debug_assert(int_value_1 == 10);
    debug::debug_assert(int_value_2 == 5);
    fmt::println_string("finish for====");




    // -----------
    fmt::println_string("[Test Case 2]");

    count = 0;

    do(int_value_1 = 0) {

        do(int_value_2 = 0) {
            count++;
            if(count == 6) {
                break 2;
            }
        }for(int_value_2<5; int_value_2++);

    }for(int_value_1<10; int_value_1++);

    fmt::println_string("finish for====");
    debug::debug_assert(count == 6);
    fmt::println_int(count);
    debug::debug_assert(int_value_1 == 0);
    debug::debug_assert(int_value_2 == 5);
    fmt::println_string("finish for====");

}
