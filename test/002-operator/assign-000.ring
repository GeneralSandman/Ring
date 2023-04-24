
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



fmt::println_string("test case1 --------");
debug::debug_assert(int_value_1 == 0);
debug::debug_assert(int_value_2 == 0);
debug::debug_assert(int_value_3 == 0);
debug::debug_assert(int_value_4 == 0);




fmt::println_string("test case2--------");
int_value_1 = 1;
int_value_2 = 2;
int_value_3 = 3;
int_value_4 = 4;

debug::debug_assert(int_value_1 == 1);
debug::debug_assert(int_value_2 == 2);
debug::debug_assert(int_value_3 == 3);
debug::debug_assert(int_value_4 == 4);




fmt::println_string("test case3--------");


int_value_1, int_value_2, int_value_3, int_value_4 = 1, 2, 3, 4;


debug::debug_assert(int_value_1 == 1);
debug::debug_assert(int_value_2 == 2);
debug::debug_assert(int_value_3 == 3);
debug::debug_assert(int_value_4 == 4);




fmt::println_string("test case4--------");


int_value_1, int_value_2 = 11, 22;
int_value_3, int_value_4 = 33, 44;


debug::debug_assert(int_value_1 == 11);
debug::debug_assert(int_value_2 == 22);
debug::debug_assert(int_value_3 == 33);
debug::debug_assert(int_value_4 == 44);




fmt::println_string("test case4--------");


int_value_1, int_value_2, int_value_3 = 111, 222, 333;
int_value_4 = 444;


debug::debug_assert(int_value_1 == 111);
debug::debug_assert(int_value_2 == 222);
debug::debug_assert(int_value_3 == 333);
debug::debug_assert(int_value_4 == 444);
}