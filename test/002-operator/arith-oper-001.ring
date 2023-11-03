
package main

import {
	fmt;
	debug;
}

@main
function main() {

	var int int_value_1, int_value_2;
	var double double_value_1, double_value_2;



	fmt::println_string("\ntest case 1");
	double_value_1 = 1.0 + 2.0*3.0 + 4.0/1.0 - 2.0;
	fmt::println_double(double_value_1);
	debug::debug_assert(double_value_1 == 9.0);


	fmt::println_string("\ntest case 2");
	int_value_1, int_value_2 = 0, 0;
	double_value_1, double_value_2 = 0.0, 0.0;


	for(int_value_1=0; int_value_1<100; int_value_1++){
	    double_value_1 += 4.0;
	    double_value_2 = double_value_2 + 4.0;
	}

	fmt::println_double(double_value_1);
	debug::debug_assert(double_value_1 == 400.0);
	fmt::println_double(double_value_2);
	debug::debug_assert(double_value_2 == 400.0);

}