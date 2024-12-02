
package main

import {
	fmt;
	debug;
}




function test() {
	var int int_value_local_1;
	var int int_value_local_2;
	var int int_value_local_3;
	var int int_value_local_4;
	var int int_value_local_5;
	var int int_value_local_6;
	var int int_value_local_7;
	var int int_value_local_8;
	var int int_value_local_9;
	var int int_value_local_10;


	int_value_local_1 = 1;
	int_value_local_2 = 2;
	int_value_local_3 = 3;
	int_value_local_4 = 4;
	int_value_local_5 = 5;
	int_value_local_6 = 6;
	int_value_local_7 = 7;
	int_value_local_8 = 8;
	int_value_local_9 = 9;
	int_value_local_10 = 10;


    fmt::println_int(int_value_local_1);
    fmt::println_int(int_value_local_2);
    fmt::println_int(int_value_local_3);
    fmt::println_int(int_value_local_4);
    fmt::println_int(int_value_local_5);
    fmt::println_int(int_value_local_6);
    fmt::println_int(int_value_local_7);
    fmt::println_int(int_value_local_8);
    fmt::println_int(int_value_local_9);
    fmt::println_int(int_value_local_10);

    debug::assert(int_value_local_1 == 1);
    debug::assert(int_value_local_2 == 2);
    debug::assert(int_value_local_3 == 3);
    debug::assert(int_value_local_4 == 4);
    debug::assert(int_value_local_5 == 5);
    debug::assert(int_value_local_6 == 6);
    debug::assert(int_value_local_7 == 7);
    debug::assert(int_value_local_8 == 8);
    debug::assert(int_value_local_9 == 9);
    debug::assert(int_value_local_10 == 10);
}

@main
function main() {

	test();
}

