
package main

import {
	fmt;
	debug;
}

@main
fn main() {
    
    var int int_value;
    
    
    // -----------
    fmt::println_string("[Test Case 1]");
    do(int_value = 0) {
        if(int_value == 5) {
            break;
        }
    }for(int_value<10; int_value++);
    
    fmt::println_string("finish for====");
    debug::assert(int_value == 5);
    fmt::println_int(int_value);
    fmt::println_string("finish for====");
}
