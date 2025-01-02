
package main

import {
	fmt;
	debug;
}



fn test(var int int_value_1, var int int_value_2, var int int_value_3) -> (int) {
    var int result = 0;

    result = result + int_value_1;
    result = result + int_value_2;
    result = result + int_value_3;

    return result;
}


fn main() {

    var int int_value;
    
    int_value = 1 + 2;
    
    int_value = test(11, 22, 33);
    fmt::println_int(int_value);
    debug::assert(int_value == 66);
    
    int_value -= test(11, 22, 33);
    fmt::println_int(int_value);
    debug::assert(int_value == 0);

}