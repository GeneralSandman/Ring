
package main

import {
	fmt;
	debug;
}

fn main() {

    var int int_value_1, int_value_2;


    fmt::println_string("\ntest case 1");

    int_value_1, int_value_2 = 0, 0;
    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 0);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 0);

    for(int_value_1=0; int_value_1<100; int_value_1++){
        int_value_2 += 4;
    }

    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 100);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 400);






    fmt::println_string("\ntest case 2");


    int_value_1, int_value_2 = 50, 52;
    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 50);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 52);

    for(; int_value_1<100; int_value_1++){
        int_value_2 += 4;
    }

    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 100);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 252);





    fmt::println_string("\ntest case 3");




    int_value_1, int_value_2 = 0, 0;
    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 0);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 0);

    for(int_value_1=0; int_value_1<100; int_value_1++){
        int_value_2 += int_value_1;
    }

    fmt::println_int(int_value_1);
    debug::assert(int_value_1 == 100);
    fmt::println_int(int_value_2);
    debug::assert(int_value_2 == 4950);

}