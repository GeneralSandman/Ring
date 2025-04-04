
package main

import {
	fmt;
	debug;
	runtime;
}


fn main() {
	test_gc_array();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
}

fn test_gc_array() {
	var int[] local_int_array_0;

	var int loop;
	for(loop = 0; loop < 100000; loop++) {
		local_int_array_0 = new int[100];
	}

}