package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_for_range_break();
	// test_for_range_continue();
}


fn test_for_range_break() {
	fmt::printf("test_for_range_break --------------------\n");

	var int[] local_int_array_0 = int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	var int index;
	var int value;
	var bool value_bool;

	// 不合法的 for-range 使用
	for(value_bool = range test()) {
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

fn test() -> (int, int) {

}
