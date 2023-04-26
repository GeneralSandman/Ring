package main

import {
	fmt;
	debug;
}

@main
function main() {

	var int int_value_1;

	int_value_1 = 101;
	fmt::println_int(int_value_1);

	int_value_1 = true ? 2 : 1; 
	fmt::println_int(int_value_1);

	int_value_1 = false ? 2 : 1; 
	fmt::println_int(int_value_1);


	int_value_1 = true ? 1+1-1*2*3*4 : 2*2*2*2 ;
	fmt::println_int(int_value_1);

	int_value_1 = false ? 1+1-1*2*3*4 : 2*2*2*2 ;
	fmt::println_int(int_value_1);


	fmt::println_string("-----");

	var int int_value_2;
	var int a;
	var int b;

	a = 10;
	b = 9;


	if(a > b) {
		int_value_2 = a;
	} else {
		int_value_2 = b;
	}
	fmt::println_int(int_value_2);



	int_value_2 = a > b ? a : b ;
	fmt::println_int(int_value_2);

}
