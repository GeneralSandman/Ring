
package main

import {
	fmt;
	debug;
	runtime;
}

fn main() {
	test_string();
}

fn test_string() {
	var string[] array_0 = string[]{"a", "a", "a", "a",};

	var string[,] array_1 = string[,]{
		array_0,
		array_0,
	};

	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);


	array_0[0] = "b";
	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);

	array_1[0,0] = "c";
	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);
}

fn test_bool() {
	var int[] array_0 = int[]{1, 2, 3, 4, 5};

	var int[,] array_1 = int[,]{
		array_0,
		array_0,
	};

	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);


	array_0[0] = 100;
	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);

	array_1[0,0] = 123;
	fmt::printf("array_0: {}\n", array_0);
	fmt::printf("array_1: {}\n", array_1);

}

