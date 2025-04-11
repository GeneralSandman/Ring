package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_for_break();
	test_for_continue();

	test_for_range_break();
	test_for_range_continue();

	test_dofor_break();
	test_dofor_continue();
}

fn test_for_break() {
	fmt::printf("test_for_break --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	for(index = 0; index < 10; index ++) {
		if (index == 5) {
			break;
		}

		fmt::printf("index = {}, value = {}\n", index, local_int_array_0[index]);
	}

	debug::assert(index == 5);
}
fn test_for_continue() {
	fmt::printf("test_for_continue --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	for(index = 0; index < 10; index ++) {
		if (index == 5) {
			continue;
		}

		fmt::printf("index = {}, value = {}\n", index, local_int_array_0[index]);
	}

	debug::assert(index == 10);
}


fn test_for_range_break() {
	fmt::printf("test_for_range_break --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	for(value = range local_int_array_0) {
		if(value == 5) {
			break;
		}
		fmt::printf("value = {}\n", value);
	}

	debug::assert(value == 5);
}
fn test_for_range_continue() {
	fmt::printf("test_for_range_continue --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	for(value = range local_int_array_0) {
		if(value == 5) {
			continue;
		}
		fmt::printf("value = {}\n", value);
	}

	debug::assert(value == 10);
}

fn test_dofor_break() {
	fmt::printf("test_dofor_break --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	do(index = 0) {
		if (index == 5) {
			break;
		}

		fmt::printf("index = {}, value = {}\n", index, local_int_array_0[index]);
	}for(index < 10; index++);

	debug::assert(index == 5);
}
fn test_dofor_continue() {
	fmt::printf("test_dofor_continue --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;

	do(index = 0) {
		if (index == 5) {
			continue;
		}

		fmt::printf("index = {}, value = {}\n", index, local_int_array_0[index]);
	}for(index < 9; index++);


	debug::assert(index == 9);
}