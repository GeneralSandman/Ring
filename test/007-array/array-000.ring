
package main

import {
    fmt;
    debug;
}

global {
}

@main
fn main() {
	var bool[] bool_array;
	var int[]  int_array;
	var int64[] int64_array;
	var double[] double_array;
	var string[] string_array;

	// fmt::println(bool_array);

	fmt::printf("-------\n");
	bool_array = bool[]{};
	int_array = int[]{};
	int64_array = int64[]{};
	double_array = double[]{};
	string_array = string[]{};
	fmt::println(bool_array);
	fmt::println(int_array);
	fmt::println(int64_array);
	fmt::println(double_array);
	fmt::println(string_array);

	fmt::printf("-------\n");
	bool_array = bool[]{true};
	int_array = int[]{1};
	int64_array = int64[]{1L};
	double_array = double[]{1.0};
	string_array = string[]{"1"};
	fmt::println(bool_array);
	fmt::println(int_array);
	fmt::println(int64_array);
	fmt::println(double_array);
	fmt::println(string_array);

}