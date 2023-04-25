
package main

import {
	fmt;
	debug;
}




function test_return_1() {
	var int int_value_local_1;
	int_value_local_1 = 1;
    return int_value_local_1++;
}


function test_return_2() {
	var int int_value_local_1;
	int_value_local_1 = 2;
    return int_value_local_1++, int_value_local_1;
}

function test_return_3() {
	var int int_value_local_1;
	int_value_local_1 = 4;
    return int_value_local_1++, int_value_local_1++, int_value_local_1;
}
@main
function main() {

var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int int_value_5;
var int int_value_6;

debug::debug_assert(int_value_1 == 0);
debug::debug_assert(int_value_2 == 0);
debug::debug_assert(int_value_3 == 0);
debug::debug_assert(int_value_4 == 0);
debug::debug_assert(int_value_5 == 0);
debug::debug_assert(int_value_6 == 0);

fmt::println_int(int_value_1);
fmt::println_int(int_value_2);
fmt::println_int(int_value_3);
fmt::println_int(int_value_4);
fmt::println_int(int_value_5);
fmt::println_int(int_value_6);



// ----------
fmt::println_string("\ntest case 1");
int_value_1 = test_return_1();
debug::debug_assert(int_value_1 == 1);
debug::debug_assert(int_value_2 == 0);
debug::debug_assert(int_value_3 == 0);
debug::debug_assert(int_value_4 == 0);
debug::debug_assert(int_value_5 == 0);
debug::debug_assert(int_value_6 == 0);

fmt::println_int(int_value_1);
fmt::println_int(int_value_2);
fmt::println_int(int_value_3);
fmt::println_int(int_value_4);
fmt::println_int(int_value_5);
fmt::println_int(int_value_6);


fmt::println_string("\ntest case 2");
int_value_1, int_value_2 = test_return_2();
debug::debug_assert(int_value_1 == 2);
debug::debug_assert(int_value_2 == 3);
debug::debug_assert(int_value_3 == 0);
debug::debug_assert(int_value_4 == 0);
debug::debug_assert(int_value_5 == 0);
debug::debug_assert(int_value_6 == 0);

fmt::println_int(int_value_1);
fmt::println_int(int_value_2);
fmt::println_int(int_value_3);
fmt::println_int(int_value_4);
fmt::println_int(int_value_5);
fmt::println_int(int_value_6);


fmt::println_string("\ntest case 3");
int_value_1, int_value_2, int_value_3 = test_return_3();
debug::debug_assert(int_value_1 == 4);
debug::debug_assert(int_value_2 == 5);
debug::debug_assert(int_value_3 == 6);
debug::debug_assert(int_value_4 == 0);
debug::debug_assert(int_value_5 == 0);
debug::debug_assert(int_value_6 == 0);


fmt::println_int(int_value_1);
fmt::println_int(int_value_2);
fmt::println_int(int_value_3);
fmt::println_int(int_value_4);
fmt::println_int(int_value_5);
fmt::println_int(int_value_6);


fmt::println_string("\ntest case 4");
int_value_1, int_value_2, int_value_3, int_value_4, int_value_5, int_value_6 = test_return_1(), test_return_2(), test_return_3();
debug::debug_assert(int_value_1 == 1);
debug::debug_assert(int_value_2 == 2);
debug::debug_assert(int_value_3 == 3);
debug::debug_assert(int_value_4 == 4);
debug::debug_assert(int_value_5 == 5);
debug::debug_assert(int_value_6 == 6);

fmt::println_int(int_value_1);
fmt::println_int(int_value_2);
fmt::println_int(int_value_3);
fmt::println_int(int_value_4);
fmt::println_int(int_value_5);
fmt::println_int(int_value_6);



}



