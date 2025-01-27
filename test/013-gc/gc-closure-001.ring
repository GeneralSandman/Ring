
package main

import {
	fmt;
	debug;
	runtime;
}

typedef FuncType = fn();

fn main() {
	// test();
	// runtime::gc();


	test_gc_array();
	runtime::gc();
}


fn test() {
	var FuncType func_var;

	func_var = fn() {
		var string local_string_value;
		local_string_value = "hello";
		fmt::println(local_string_value);
	};

	func_var();
}

fn test_gc_array() {
	var int[] local_int_array_0;

	var int loop;
	for(loop = 0; loop < 100000; loop++) {
		local_int_array_0 = new int[100];
	}

}