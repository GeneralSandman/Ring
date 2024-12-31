package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

@main
fn main() {
	global_int_array_0 = func_return_int_array();
	
	fmt::println_string("\n=================func main\n");
	fmt::println_int(global_int_array_0[0]);
	fmt::println_int(global_int_array_0[1]);
	fmt::println_int(global_int_array_0[2]);
	fmt::println_int(global_int_array_0[3]);
	fmt::println_int(global_int_array_0[4]);
	fmt::println_int(global_int_array_0[5]);
	fmt::println_int(global_int_array_0[6]);
	fmt::println_int(global_int_array_0[7]);
	fmt::println_int(global_int_array_0[8]);
	fmt::println_int(global_int_array_0[9]);
	fmt::println_int(global_int_array_0[10]);
	fmt::println_int(global_int_array_0[11]);
	fmt::println_int(global_int_array_0[12]);
	fmt::println_int(global_int_array_0[13]);
	fmt::println_int(global_int_array_0[14]);

	debug::assert(global_int_array_0[0]  == 0);
	debug::assert(global_int_array_0[1]  == 1);
	debug::assert(global_int_array_0[2]  == 2);
	debug::assert(global_int_array_0[3]  == 3);
	debug::assert(global_int_array_0[4]  == 4);
	debug::assert(global_int_array_0[5]  == 5);
	debug::assert(global_int_array_0[6]  == 6);
	debug::assert(global_int_array_0[7]  == 7);
	debug::assert(global_int_array_0[8]  == 8);
	debug::assert(global_int_array_0[9]  == 9);
	debug::assert(global_int_array_0[10] == 10);
	debug::assert(global_int_array_0[11] == 11);
	debug::assert(global_int_array_0[12] == 12);
	debug::assert(global_int_array_0[13] == 13);
	debug::assert(global_int_array_0[14] == 14);
}

fn func_return_int_array() -> (int[]) {
	var int[] int_array = int[]{0, 1, 2, 
		3, 4, 5, 
		6, 7, 8, 
		9, 10, 11, 
		12, 13, 14};
	
	fmt::println_string("=================func func_return_int_array\n");
	fmt::println_int(int_array[0]);
	fmt::println_int(int_array[1]);
	fmt::println_int(int_array[2]);
	fmt::println_int(int_array[3]);
	fmt::println_int(int_array[4]);
	fmt::println_int(int_array[5]);
	fmt::println_int(int_array[6]);
	fmt::println_int(int_array[7]);
	fmt::println_int(int_array[8]);
	fmt::println_int(int_array[9]);
	fmt::println_int(int_array[10]);
	fmt::println_int(int_array[11]);
	fmt::println_int(int_array[12]);
	fmt::println_int(int_array[13]);
	fmt::println_int(int_array[14]);

	debug::assert(int_array[0]  == 0);
	debug::assert(int_array[1]  == 1);
	debug::assert(int_array[2]  == 2);
	debug::assert(int_array[3]  == 3);
	debug::assert(int_array[4]  == 4);
	debug::assert(int_array[5]  == 5);
	debug::assert(int_array[6]  == 6);
	debug::assert(int_array[7]  == 7);
	debug::assert(int_array[8]  == 8);
	debug::assert(int_array[9]  == 9);
	debug::assert(int_array[10] == 10);
	debug::assert(int_array[11] == 11);
	debug::assert(int_array[12] == 12);
	debug::assert(int_array[13] == 13);
	debug::assert(int_array[14] == 14);

	return int_array;
}