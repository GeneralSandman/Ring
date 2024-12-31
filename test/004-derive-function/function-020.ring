
package main

import {
	fmt;
	debug;
}



fn fibonacci_1(var int num) -> (int) {
    if(num == 1 or num == 2) {
        return 1;
    } else {
        return fibonacci_1(num-1) + fibonacci_1(num-2);
    }
}

fn fibonacci_2(var int num) -> (int) {
    if(num < 3) {
        return 1;
    }


    var int a, b = 1, 1;
    var int i;
    var int tmp;
    for(i = 3; i <= num; i++){
        tmp = a + b;
        a = b;
        b = tmp;
    }
    return tmp;

}


@main
fn main() {

    fmt::println_string("\ntest case 1");
    fmt::println_int(fibonacci_1(1));
    fmt::println_int(fibonacci_1(2));
    fmt::println_int(fibonacci_1(3));
    fmt::println_int(fibonacci_1(4));
    fmt::println_int(fibonacci_1(5));
    fmt::println_int(fibonacci_1(6));
    fmt::println_int(fibonacci_1(7));
    fmt::println_int(fibonacci_1(8));
    fmt::println_int(fibonacci_1(9));
    fmt::println_int(fibonacci_1(10));



    fmt::println_string("\ntest case 2");
    fmt::println_int(fibonacci_2(1));
    fmt::println_int(fibonacci_2(2));
    fmt::println_int(fibonacci_2(3));
    fmt::println_int(fibonacci_2(4));
    fmt::println_int(fibonacci_2(5));
    fmt::println_int(fibonacci_2(6));
    fmt::println_int(fibonacci_2(7));
    fmt::println_int(fibonacci_2(8));
    fmt::println_int(fibonacci_2(9));
    fmt::println_int(fibonacci_2(10));


    fmt::println_string("\ntest case 3");
    debug::assert(fibonacci_1(1) == fibonacci_2(1));
    debug::assert(fibonacci_1(2) == fibonacci_2(2));
    debug::assert(fibonacci_1(3) == fibonacci_2(3));
    debug::assert(fibonacci_1(4) == fibonacci_2(4));
    debug::assert(fibonacci_1(5) == fibonacci_2(5));
    debug::assert(fibonacci_1(6) == fibonacci_2(6));
    debug::assert(fibonacci_1(7) == fibonacci_2(7));
    debug::assert(fibonacci_1(8) == fibonacci_2(8));
    debug::assert(fibonacci_1(9) == fibonacci_2(9));
    debug::assert(fibonacci_1(10) == fibonacci_2(10));
    debug::assert(fibonacci_1(11) == fibonacci_2(11));
    debug::assert(fibonacci_1(12) == fibonacci_2(12));
    debug::assert(fibonacci_1(13) == fibonacci_2(13));
    debug::assert(fibonacci_1(14) == fibonacci_2(14));
    debug::assert(fibonacci_1(15) == fibonacci_2(15));
    debug::assert(fibonacci_1(16) == fibonacci_2(16));
    debug::assert(fibonacci_1(17) == fibonacci_2(17));
    debug::assert(fibonacci_1(18) == fibonacci_2(18));
    debug::assert(fibonacci_1(19) == fibonacci_2(19));
    debug::assert(fibonacci_1(20) == fibonacci_2(20));
    debug::assert(fibonacci_1(21) == fibonacci_2(21));
    debug::assert(fibonacci_1(22) == fibonacci_2(22));
    debug::assert(fibonacci_1(23) == fibonacci_2(23));
    debug::assert(fibonacci_1(24) == fibonacci_2(24));
    debug::assert(fibonacci_1(25) == fibonacci_2(25));


}