
package main

import {
	fmt;
	debug;
}

@main
function main() {

var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int count;

// -----------
fmt::println_string("[Test Case 1]");

count = 0;

for(int_value_1 = 0; int_value_1<10; int_value_1++){
    do(int_value_2 = 0) {


        for(int_value_3 = 0; int_value_3<10; int_value_3++){
            do(int_value_4 = 0) {
        
                count++;

            }for(int_value_4<9; int_value_4++);
        }

    }for(int_value_2<9; int_value_2++);
}

fmt::println_string("finish for====");
debug::debug_assert(count == 10 * 10 * 10 * 10);
fmt::println_int(count);
debug::debug_assert(int_value_1 == 10);
debug::debug_assert(int_value_2 == 9);
debug::debug_assert(int_value_3 == 10);
debug::debug_assert(int_value_4 == 9);
fmt::println_string("finish for====");


}

