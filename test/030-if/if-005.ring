
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

	int_value_1 = 1;
	int_value_2 = 2;
	int_value_3 = 3;
	if(int_value_1 < int_value_2 and int_value_2 < int_value_3) {
		fmt::println_string("check (int_value_1 < int_value_2 and int_value_2 < int_value_3) pass\n");
	} else {
		fmt::println_string("check (int_value_1 < int_value_2 and int_value_2 < int_value_3) failed\n");
	}


	if(int_value_1 <= int_value_2 and int_value_2 < int_value_3) {
		fmt::println_string("check (int_value_1 <= int_value_2 and int_value_2 < int_value_3) pass\n");
	} else {
		fmt::println_string("check (int_value_1 <= int_value_2 and int_value_2 < int_value_3) failed\n");
	}


	if(int_value_1 > int_value_2 or int_value_2 < int_value_3) {
		fmt::println_string("check (int_value_1 > int_value_2 or int_value_2 < int_value_3) pass\n");
	} else {
		fmt::println_string("check (int_value_1 > int_value_2 or int_value_2 < int_value_3) failed\n");
	}

}
