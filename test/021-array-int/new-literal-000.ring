package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

@main
function main() {
	global_int_array_0 = int[]{0, 1, 2, 
		3, 4, 5, 
		6, 7, 8, 
		9, 10, 11, 
		12, 13, 14};
	

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