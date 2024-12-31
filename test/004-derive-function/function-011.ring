
package main

import {
	fmt;
	debug;
}



global {
    var int int_value_global_1;
    var int int_value_global_2;
}




fn test_1(var int int_value_1, var int int_value_2) -> (int, int) {
    fmt::println_string("function test_1");

    fmt::println_int(int_value_1);
    fmt::println_int(int_value_2);

    debug::assert(int_value_1 == 123);
    debug::assert(int_value_2 == 234);

    return int_value_1, int_value_2;

}

@main
fn main() {
    debug::assert(int_value_global_1 == 0);
    debug::assert(int_value_global_2 == 0);

    int_value_global_1, int_value_global_2 = test_1(123, 234);

    debug::assert(int_value_global_1 == 123);
    debug::assert(int_value_global_2 == 234);

}
