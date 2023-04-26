
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

	var int tmp;


	fmt::println_string("test case1 --------");
	debug::debug_assert(int_value_1 == 0);
	debug::debug_assert(int_value_2 == 0);
	debug::debug_assert(int_value_3 == 0);
	debug::debug_assert(int_value_4 == 0);




	fmt::println_string("test case2 --------");
	tmp = 1;
	int_value_1 = tmp++;
	int_value_2 = tmp++;
	int_value_3 = tmp++;
	int_value_4 = tmp++;

	debug::debug_assert(int_value_1 == 1);
	debug::debug_assert(int_value_2 == 2);
	debug::debug_assert(int_value_3 == 3);
	debug::debug_assert(int_value_4 == 4);


	fmt::println_string("test case3 --------");
	tmp = 1;
	int_value_1 = ++tmp;
	int_value_2 = ++tmp;
	int_value_3 = ++tmp;
	int_value_4 = ++tmp;

	debug::debug_assert(int_value_1 == 2);
	debug::debug_assert(int_value_2 == 3);
	debug::debug_assert(int_value_3 == 4);
	debug::debug_assert(int_value_4 == 5);





	fmt::println_string("test case4 --------");
	tmp = 1;
	int_value_1, int_value_2, int_value_3, int_value_4 = tmp++, tmp++, tmp++, tmp++;

	debug::debug_assert(int_value_1 == 1);
	debug::debug_assert(int_value_2 == 2);
	debug::debug_assert(int_value_3 == 3);
	debug::debug_assert(int_value_4 == 4);



	fmt::println_string("test case5 --------");
	tmp = 1;
	int_value_1, int_value_2, int_value_3, int_value_4 = ++tmp, ++tmp, ++tmp, ++tmp;

	debug::debug_assert(int_value_1 == 2);
	debug::debug_assert(int_value_2 == 3);
	debug::debug_assert(int_value_3 == 4);
	debug::debug_assert(int_value_4 == 5);




	fmt::println_string("test case6 --------");
	tmp = 1;
	int_value_1, int_value_2 = ++tmp, ++tmp;
	int_value_3, int_value_4 = ++tmp, ++tmp;

	debug::debug_assert(int_value_1 == 2);
	debug::debug_assert(int_value_2 == 3);
	debug::debug_assert(int_value_3 == 4);
	debug::debug_assert(int_value_4 == 5);

}