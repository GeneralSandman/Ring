package main

import {
	fmt;
	debug;
}

fn main() {

	var bool bool_value_1;

	var int int_value_1, int_value_2;

	var double double_value_1, double_value_2;



	fmt::println_string("\ntest case 1");
	int_value_1 = 1;
	int_value_2 = 2;
	debug::assert(1 <  2);
	debug::assert(1 <= 2);
	debug::assert(int_value_1 <  int_value_2);
	debug::assert(int_value_1 <= int_value_2);


	fmt::println_string("\ntest case 2");
	int_value_1 = -65536;
	int_value_2 = 65535;
	debug::assert(-65536 <  65535);
	debug::assert(-65536 <= 65535);
	debug::assert(int_value_1 <  int_value_2);
	debug::assert(int_value_1 <= int_value_2);

	debug::assert(65536 >  65535);
	debug::assert(65536 >= 65535);
	// debug::assert(-int_value_1 >  int_value_2); // FIXME: BUG segment fault
	// debug::assert(-int_value_1 >= int_value_2); // FIXME: BUG segment fault





	fmt::println_string("\ntest case 3");
	double_value_1 = 1.23456;
	double_value_2 = 1.2345;
	debug::assert(1.23456 >  1.2345);
	debug::assert(1.23456 >= 1.2345);
	debug::assert(double_value_1 > double_value_2);
	debug::assert(double_value_1 >= double_value_2);


	fmt::println_string("\ntest case 4");
	double_value_1 = 65535.23456;
	double_value_2 = 65536.2345;
	debug::assert(65535.23456 <  65536.2345);
	debug::assert(65535.23456 <= 65536.2345);
	debug::assert(double_value_1 < double_value_2);
	debug::assert(double_value_1 <= double_value_2);



	fmt::println_string("\ntest case 5");
	double_value_1 = 65535.23456;
	double_value_2 = 65536.2345;
	debug::assert(65535.23456 <  65536.2345);
	debug::assert(65535.23456 <= 65536.2345);
	debug::assert(double_value_1 < 65536.2345);
	debug::assert(double_value_1 <= 65536.2345);


	fmt::println_string("\ntest case 6");
	double_value_1 = 1.23456;
	double_value_2 = 1.2345;
	debug::assert(1.23456 >  double_value_2);
	debug::assert(1.23456 >= double_value_2);
	debug::assert(double_value_1 > 1.2345);
	debug::assert(double_value_1 >= 1.2345);

}