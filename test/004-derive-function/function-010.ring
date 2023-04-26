
package main

import {
	fmt;
	debug;
}




function test(var int int_value_1, var int int_value_2) {
	var int int_value_3;
	var int int_value_4;

    int_value_1 = 1;
    int_value_2 = 2;
    int_value_3 = 3;
    int_value_4 = 4;

    fmt::println_int(int_value_1);
    fmt::println_int(int_value_2);
    fmt::println_int(int_value_3);
    fmt::println_int(int_value_4);

    return int_value_1, int_value_2, int_value_3, int_value_4;
}

@main
function main() {
    var int int_value_1;
    var int int_value_2;
    var int int_value_3;
    var int int_value_4;

    debug::debug_assert(int_value_1 == 0);
    debug::debug_assert(int_value_2 == 0);
    debug::debug_assert(int_value_3 == 0);
    debug::debug_assert(int_value_4 == 0);

    fmt::println_int(int_value_1);
    fmt::println_int(int_value_2);
    fmt::println_int(int_value_3);
    fmt::println_int(int_value_4);



    fmt::println_string("\ntest case 1");
    int_value_1, int_value_2, int_value_3, int_value_4 = test(0, 0);

    debug::debug_assert(int_value_1 == 1);
    debug::debug_assert(int_value_2 == 2);
    debug::debug_assert(int_value_3 == 3);
    debug::debug_assert(int_value_4 == 4);
    return 0;

}
